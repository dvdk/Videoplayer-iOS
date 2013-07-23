//
//  BCSDKMediaService.m
//  CatalogPlaylistApp
//
//  Created by Tom Abbott on 4/11/13.
//  Copyright (c) 2013 brightcove. All rights reserved.
//

#import "BCSDKMediaService.h"
#import "BCVideo.h"
#import "BCEvent.h"
#import "BCCuePoint.h"
#import "BCRendition.h"
#import "BCRenditionSet.h"

#define NULL_TO_NIL(obj) ({ __typeof__ (obj) __obj = (obj); __obj == [NSNull null] ? nil : obj; })

@interface BCSDKMediaService ()

@property (nonatomic, strong) NSString *iu;

@end


@implementation BCSDKMediaService

NSUInteger pod;

- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter token:(NSString *)token baseURL:(NSString *)baseURL iu:(NSString *) iu;
{
    if(self = [super initWithEventEmitter:eventEmitter token:token baseURL:baseURL]) {
        _iu = iu;
    }
               
   return self;
}

-(BCVideo *)makeVideoWithJSON:(NSDictionary *)json
{

    NSMutableDictionary *properties = [[NSMutableDictionary alloc] init];
    NSDictionary *wvmRendition = nil;
    
    // Checking !=NULL, !=Nil, isEqual:Nil are not sufficient for JSON or dictionary objects.
    if([json objectForKey:@"WVMRenditions"] && ![[json objectForKey:@"WVMRenditions"] isEqual:[NSNull null]]) {
        NSArray *wvmRenditions = (NSArray *) [json objectForKey:@"WVMRenditions"];
        [properties setValue:wvmRenditions forKey:@"WVMRenditions"];
        
        if ([wvmRenditions count] > 0) {
            wvmRendition = [wvmRenditions objectAtIndex:0];
            [properties setValue:[wvmRendition objectForKey:@"videoDuration"] forKey:@"duration"];
        }
    }
    if ([json objectForKey:@"videoStillURL"] && ![[json objectForKey:@"videoStillURL"] isEqual:[NSNull null]]) {
        [properties setValue:[NSURL URLWithString:[json objectForKey:@"videoStillURL"]] forKey:@"videoStillURL"];
    }
    if ([json objectForKey:@"name"] && ![[json objectForKey:@"name"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"name"] forKey:@"name"];
    }
    if ([json objectForKey:@"shortDescription"] && ![[json objectForKey:@"shortDescription"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"shortDescription"] forKey:@"shortDescription"];
    }
    if ([json objectForKey:@"referenceId"] && ![[json objectForKey:@"referenceId"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"referenceId"]] forKey:@"referenceID"];
    }
    if ([json objectForKey:@"id"] && ![[json objectForKey:@"id"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"id"]] forKey:@"videoID"];
    }
    if ([json objectForKey:@"customFields"] && ![[json objectForKey:@"customFields"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"customFields"] forKey:@"customFields"];
    }
    if ([json objectForKey:@"pubID"] && ![[json objectForKey:@"pubId"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"pubID"]] forKey:@"pubID"];
    }
    
    if (![properties objectForKey:@"pubID"]) {
        // Use regex to pull out a pubID - YAY :D
        NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"pubId=(\\d+)"
                                                                               options:0
                                                                                 error:nil];
        NSString *string = [NSString stringWithFormat:@"%@", [json objectForKey:@"videoStillURL"]];
        NSTextCheckingResult *match = [regex firstMatchInString:string
                                                        options:0
                                                          range:NSMakeRange(0, [string length])];
        if (!match) {
            string = [NSString stringWithFormat:@"%@", [json objectForKey:@"thumbnailURL"]];
            match = [regex firstMatchInString:string
                                      options:0
                                        range:NSMakeRange(0, [string length])];
        }
        if (!match) {
            string = [NSString stringWithFormat:@"%@", [json objectForKey:@"FLVURL"]];
            match = [regex firstMatchInString:string
                                      options:0
                                        range:NSMakeRange(0, [string length])];
        }
        if (match) {
            [properties setValue:[string substringWithRange:[match rangeAtIndex:1]]
                          forKey:@"pubID"];
        }
    }
    
    BCRendition *rendition = nil;
    BCRenditionSet *renditionSet = nil;
    
    if (wvmRendition) {
        rendition = [[BCRendition alloc] initWithURL:[NSURL URLWithString:[wvmRendition objectForKey:@"url"]]];
    } else {
        // if no widevine rendition is found, attempt to playback the FLVURL as a normal video.
        rendition = [[BCRendition alloc] initWithURL:[NSURL URLWithString:[json objectForKey:@"FLVURL"]]];
    }
    renditionSet = [[BCRenditionSet alloc] initWithRenditions:[NSArray arrayWithObject:rendition]
                                               deliveryMethod:[NSDictionary dictionary]];
    
    BCVideo *video = [[BCVideo alloc] initWithRenditionSets: [NSArray arrayWithObject:renditionSet]
                                       properties: [NSDictionary dictionaryWithDictionary:properties]];

    // Add cue points to video
    NSArray *cuepoints = [self extractCuepointsFromJson:json];
    return [video withCuePoints:cuepoints];
}

- (NSArray *) extractCuepointsFromJson:(NSDictionary *) json
{
    NSInteger videoLength;
    
    // Extract length, we require this to determine post rolls
    videoLength = [NULL_TO_NIL([json objectForKey:@"length"]) integerValue] / 1000;
    
    // Iterate through cuepoints
    NSArray *jsonCuepoints = NULL_TO_NIL([json objectForKey:@"cuePoints"]);
    NSMutableSet *cuepointTimes = [[NSMutableSet alloc] init];
    for (NSDictionary *jsonCuepoint in jsonCuepoints) {
        // Ignore cuepoints that aren't ADs
        NSString *typeEnum = NULL_TO_NIL([jsonCuepoint objectForKey:@"typeEnum"]);
        if ([typeEnum isEqualToString:@"AD"]) {
            NSInteger timeInSecs = [NULL_TO_NIL([jsonCuepoint objectForKey:@"time"]) integerValue] / 1000;
            
            // For now lets ignore pre/post rolls, they're not always here we can add them ourselves later
            if ((timeInSecs != 0) && (timeInSecs != videoLength)) {
                [cuepointTimes addObject:[NSNumber numberWithInt:timeInSecs]];
            }
        }
    }
    
    NSArray *prerollPoints = [self createPrerollCuepoints];
    NSArray *midrollPoints = [self createMidrollCuepointsFromTimes:cuepointTimes];
    NSArray *postrollPoints = [self createPostrollCuepoints];
    
    NSMutableArray *cuePoints = [[NSMutableArray alloc] initWithArray:prerollPoints];
    [cuePoints addObjectsFromArray:midrollPoints];
    [cuePoints addObjectsFromArray:postrollPoints];
    return cuePoints;
}

// Returns an array of pre roll points based on rules for plus 7 (1 preroll + 1 bumper)
- (NSArray *) createPrerollCuepoints
{
    BCCuePoint *preroll = [BCCuePoint cuePointWithPosition:@"before" type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"preroll" pod:1 ppos:1 minmms:15000 maxms:30000 lip:NO bumper:nil]}];
    BCCuePoint *prebump = [BCCuePoint cuePointWithPosition:@"before" type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"preroll" pod:1 ppos:0 minmms:15000 maxms:30000 lip:YES bumper:@"after"]}];
    NSArray *prerollPoints = @[preroll, prebump];
    
    return prerollPoints;
}

// Returns an array of BCCuePoints for each midroll in the set of cuetimes
- (NSArray *) createMidrollCuepointsFromTimes:(NSSet *) cuetimes
{
    NSMutableArray *midrollPoints = [[NSMutableArray alloc] init];
    NSArray *times = [[cuetimes allObjects] sortedArrayUsingSelector:@selector(compare:)];
    
    for (NSNumber *time in times) {
        NSArray *cuepointsForTime = [self midrollCuepointsForTime:time pod:pod];
        [midrollPoints addObjectsFromArray:cuepointsForTime];
        pod++;
    }
    
    return midrollPoints;
}

// Generate an array of BCCuePoints for a time based on Plus7 rulles (each midroll time has 2 ads + 1 bumper)
- (NSArray *) midrollCuepointsForTime:(NSNumber *) time pod:(NSUInteger) pod
{
    NSString *position = [time stringValue];
    BCCuePoint *mid1 = [BCCuePoint cuePointWithPosition:position type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"midroll" pod:pod ppos:1 minmms:15000 maxms:30000 lip:NO bumper:nil]}];
    BCCuePoint *mid2 = [BCCuePoint cuePointWithPosition:position type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"midroll" pod:pod ppos:2 minmms:15000 maxms:30000 lip:NO bumper:nil]}];

    BCCuePoint *midbump = [BCCuePoint cuePointWithPosition:position type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"midroll" pod:pod ppos:0 minmms:15000 maxms:30000 lip:YES bumper:@"after"]}];
    NSArray *midrollPoints = @[mid1, mid2, midbump];
    
    return midrollPoints;
}


// Returns an array of BCCuePoints for post roll ads
- (NSArray *) createPostrollCuepoints
{
    
    /*
    BCCuePoint *postroll = [BCCuePoint cuePointWithPosition:@"after" type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"postroll" pod:pod ppos:1 minmms:15000 maxms:30000 lip:NO bumper:nil]}];
    BCCuePoint *postbump = [BCCuePoint cuePointWithPosition:@"after" type:@"ad" properties:@{ @"tag": [self dfpUrlForVpos:@"postroll" pod:pod ppos:0 minmms:15000 maxms:30000 lip:YES bumper:@"after"]}];
    NSArray *postrollPoints = @[postroll, postbump];
    return postrollPoints;
    */
    
    // Brightcove iOS SDK does not support post rolls at this stage. Retun nill
    return nil;
}


/**
 * Generates a DFP vast url based on various params
 * version of the constructor allows you to optionally specify a URL for the
 * media API to use. Developers who are not using Brightcove in Japan probably
 * want to use the version of this method that does not have a base URL
 * parameter instead.
 *
 * @param vpos either 'preroll', 'midroll' or 'postroll'
 * @param pod int - the ad position starting at 1 for preroll slot, 2 for first midroll slot etc
 * @param ppos int - positiong in pod 1 based ie if there are 2 prerolls this would be 1/2
 * @param minms int - minimum number of milliseconds for an ad eg 15000
 * @param maxms int - maximum number of milliseconds for an ad eg 30000
 * @param maxms lip - is this the last ad in a particular pod
 * @param bumper either 'before' or 'after' for bumper ads, or nil for regular ads
 */
- (NSString *) dfpUrlForVpos:(NSString *) vpos pod:(NSUInteger) pod ppos:(NSUInteger) ppos minmms:(NSUInteger) minms maxms:(NSUInteger) maxms lip:(BOOL) lip bumper:(NSString *) bumper
{
    NSString *lipStr = lip ? @"&lip=true" : @"";
    NSTimeInterval ts = [[NSDate date] timeIntervalSince1970];
    NSString *bumperOrPPos = (bumper != nil) ? [NSString stringWithFormat:@"bumper=%@", bumper] : [NSString stringWithFormat:@"&ppos=%u", ppos];
    NSString *url = [NSString stringWithFormat:@"http://pubads.g.doubleclick.net/gampad/ads?sz=400x300&iu=%@&ciu_szs&impl=s&gdfp_req=1&env=vp&output=xml_vast2&unviewed_position_start=1&ad_rule=0&vad_type=linear&vpos=%@&pod=%u%@&min_ad_duration=%u&max_ad_duration=%u&%%20rl=[referrer_url]&correlator=%f%@", self.iu, vpos, pod, bumperOrPPos, minms, maxms, ts, lipStr];
    return url;    
}

@end
