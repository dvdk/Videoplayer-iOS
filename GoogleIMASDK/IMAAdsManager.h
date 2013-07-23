//
//  IMAAdsManager.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//
//  Declares IMAAdsManager interface that manages loading and unloading ads.

#import <Foundation/Foundation.h>

#pragma mark IMAAdsManagerType

/// Supported AdsManager Types
typedef enum {
  kIMAAdsManagerTypeVideo,
} IMAAdsManagerType;

#pragma mark -

/// The IMAAdsManager class is responsible for loading and playing ads.
@interface IMAAdsManager : NSObject

/// Stops playing the ad and unloads the ad asset.
//
/// Removes ad assets at runtime that need to be properly removed at the time
/// of ad completion amd stops the ad and removes tracking.
- (void)unload;

/// Returns the AdsManager type.
@property(readonly, assign) IMAAdsManagerType adsManagerType;

/// List of ads managed by the ads manager.
@property(readonly, retain) NSArray *ads;

@end
