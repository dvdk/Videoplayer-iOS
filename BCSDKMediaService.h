//
//  BCSDKMediaService.h
//  CatalogPlaylistApp
//
//  Created by Tom Abbott on 4/11/13.
//  Copyright (c) 2013 brightcove. All rights reserved.
//

#import "BCMediaService.h"

/**
 * A custom SDK Media Service to handle the
 * additional values coming back from the media API
 */
@interface BCSDKMediaService : BCMediaService

/**
 * We are extending initWithEventEmitter:token:baseURL with a method that takes in an iu param
 * iu is required for setting DFP urls used in BCCuePoint tags
 *
 * Initialize a new media service object with the specified event emitter. This
 * version of the constructor allows you to optionally specify a URL for the
 * media API to use. Developers who are not using Brightcove in Japan probably
 * want to use the version of this method that does not have a base URL
 * parameter instead.
 *
 * @param eventEmitter the event emitter to listend and respond to events on
 * @param token the API token to use for requests.
 * @param the base URL of the media API to use. Optional.
 * @param the iu string to be used for DFP ad calls in BCCuePoints
 */
- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter token:(NSString *)token baseURL:(NSString *)baseURL iu:(NSString *) iu;

/**
 * We are overriding makeVideoWithJSON to handle any
 * additional media API fields we want to set on the
 * video properties
 */
-(BCVideo *)makeVideoWithJSON:(NSDictionary *)json;

@end
