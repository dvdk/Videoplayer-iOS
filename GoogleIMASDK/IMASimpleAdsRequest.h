//
//  IMASimpleAdsRequest.h
//  GoogleIMA
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMAAdsRequest.h"

#pragma mark IMASimpleAdsRequestAdType

/// Supported ad types for simple DoubleClick ad requests.
typedef enum {
  /// An ad type that the SDK doesn't know about.
  kIMASimpleAdsRequestAdTypeUnknown = -1,
  /// Request to play VAST video ads.
  kIMASimpleAdsRequestAdTypeVideo = 0
} IMASimpleAdsRequestAdType;

#pragma mark -

/// AdsRequest for loading ads from DoubleClick ad server.
@interface IMASimpleAdsRequest : IMAAdsRequest

/// Specifies full URL to use for ads loading from DoubleClick ad server.
//
/// This is a required parameter for making DoubleClick ads request.
@property(nonatomic, copy) NSString *adTagUrl;

/// Specifies the ad type of the requested ad.
//
/// \throw IMAAdError if invalid ad type value is provided.
/// This is optional and would default to video ad type.
@property(assign) IMASimpleAdsRequestAdType adType;

@end
