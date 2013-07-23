//
//  IMAVideoAd.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//
//  Declares IMAVideoAd interface that has the representation of a video ad.

#import "IMAAd.h"

/// This class represents a video ad. It can be a streaming or progressive ad.
@interface IMAVideoAd : IMAAd

/// The length of the media file in seconds. Returns -1 if the duration value
/// is not available.
@property(readonly, assign) float duration;

/// The URL of the media file chosen from the ad to play. Returns null if the
/// information is not available.
@property(readonly, retain) NSString *mediaUrl;

@end
