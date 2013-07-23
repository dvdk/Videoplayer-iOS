//
//  BCOVViewController.m
//  BrightcoveIMASamplePreMid
//
//  Created by Tom Abbott on 7/3/13.
//  Copyright (c) 2013 Brightcove. All rights reserved.
//

#import "BCOVViewController.h"

#import "BCVideo.h"
#import "BCQueuePlayer.h"
#import "BCUIControls.h"
#import "BCPlaylist.h"
#import "BCEvent.h"
#import "BCError.h"
#import "BCCuePoint.h"
#import "BCEventEmitterProtocol.h"
#import "BCEventEmitter.h"
#import "BCEventLogger.h"

#import "BCKIMAPlugin.h"
#import "BCKIMAConstants.h"
#import "IMAClickTrackingUIView.h"
#import "EmulatedControls.h"
#import "BCWidevinePlugin.h"

#import "BCSDKCatalog.h"
#define ACCOUNT_TOKEN @"" // TODO
#define REFERENCE_ID @"17880150"
#define DFP_IU @"" // TODO

@interface BCOVViewController()
{
    BCSDKCatalog *bcc;
    BCVideoResponseBlock responseBlock;
    BCWidevinePlugin *widevinePlugin;
    BCEventEmitter *emitter;
    BCEventLogger *logger;
}
@end

@implementation BCOVViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self fetchVideoByReferenceId:REFERENCE_ID iu:DFP_IU];
}

- (void) fetchVideoByReferenceId:(NSString *) assetId iu:(NSString *) iu
{
    bcc = [[BCSDKCatalog alloc] initWithToken:ACCOUNT_TOKEN baseURL:nil iu:iu];
    
    BCOVViewController __weak *weakself = self;
    responseBlock =  ^(BCError *error, BCVideo *video) {
        if (video != nil) {
            [weakself configurePlayer:@[video]];
        } else if (error != nil) {
            NSLog(@"Error fetching video %@", error);
        }
    };
    
    // All but last three are required by player. Do not remove
    NSString *videoFields = @"FLVFullLength,videoStillURL,name,shortDescription,referenceId,id,customFields,FLVURL,cuepoints,length,WVMRenditions";
    NSDictionary *options = @{@"video_fields" : videoFields};
    [bcc findVideoByReferenceID:assetId options:options callBlock:responseBlock];
}

- (void)configurePlayer:(NSArray *)videos
{
    widevinePlugin = [[BCWidevinePlugin alloc] initWithToken:ACCOUNT_TOKEN baseURL:nil];
    self.player = widevinePlugin.player;
    emitter = self.player.playbackEmitter;

    // enable logging.
    [emitter emit:BCEventSetDebug withDetails:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES]
                                                                                    forKey:@"debug"]];
    logger = [[BCEventLogger alloc] initWithEventEmitter:emitter];
    [logger setVerbose:NO];
    
    //Add UI Controls - need to register this *before* IMA plugin as it steals BCEventCuepoint events on seek
    self.controls = [[EmulatedControls alloc] initWithEventEmitter:self.player.playbackEmitter parent:self];
    
    // Create an ad plugin
    self.imaPlugin = [[BCKIMAPlugin alloc] initWithEmitter:emitter adContainer:self.adView];
    self.imaPlugin.adPolicy = ^(BCVideo *video){
        return video.cuePoints;
    };
    [self.imaPlugin configure];
    
    // Set a playlist
    BCPlaylist *playlist = [[BCPlaylist alloc] initWithVideos:videos];
    [self.player insertPlaylist:playlist afterItem:nil];
    
    //Add player to view
    widevinePlugin.player.view.frame = self.playerView.frame;
    self.player.view.autoresizingMask = UIViewAutoresizingFlexibleHeight|UIViewAutoresizingFlexibleWidth;
    [self.playerView addSubview:self.player.view];
        
    // Prevent mute switch from muting video player
    NSError *_error = nil;
    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: &_error];
    
    //Play on Player
    [self.player play];
    //[self.player airPlayVideoActive];
}

#pragma mark IMAClickThroughBrowserDelegate Impl

- (void)browserDidOpen
{
    // Browser opened
}

- (void)browserDidClose
{
    // Browser closed
}
@end
