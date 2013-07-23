//
//  IMAVideoAd.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//
//  Declares IMAAd interface that has the general representation of an ad.

#import <Foundation/Foundation.h>

#pragma mark IMAAdType

/// Supported Ad Types
typedef enum {
  kIMAAdTypeVideo,
} IMAAdType;

#pragma mark -

/// The IMAAd class that represents different ad types.
@interface IMAAd : NSObject

/// The ad type.
@property(readonly, assign) IMAAdType adType;

/// The id of the ad, null if information is not available.
@property(readonly, retain) NSString *adId;

/// Width of the ad creative.
@property(readonly, assign) float creativeWidth;

/// Height of the ad creative.
@property(readonly, assign) float creativeHeight;

@end

