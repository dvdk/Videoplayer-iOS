//
//  IMAAdError.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//
//  This file provides error codes that are raised internally by the SDK and
//  declares the IMAAdError instance.

#import <Foundation/Foundation.h>

#pragma mark IMAErrorType

/// Possible error types while loading or playing ads.
typedef enum {
  /// An unexpected error occured while loading or playing the ads.
  //
  /// This may mean that the SDK wasn't loaded properly.
  kIMAAdUnknownErrorType,
  /// An error occured while loading the ads.
  kIMAAdLoadingFailed,
  /// An error occured while playing the ads.
  kIMAAdPlayingFailed,
} IMAErrorType;

#pragma mark -
#pragma mark IMAErrorCode

/// Possible error codes raised while loading or playing ads.
typedef enum {
  /// Unknown error occured while loading or playing the ad.
  kIMAUnknownErrorCode = 0,
  /// There was an error playing the video ad.
  kIMAVideoPlayError = 1003,
  /// There was a problem requesting ads from the server.
  kIMAFailedToRequestAds = 1004,
  /// There was an internal error while loading the ad.
  kIMAInternalErrorWhileLoadingAds = 2001,
  /// No supported ad format was found.
  kIMASupportedAdsNotFound = 2002,
  /// At least one VAST wrapper ad loaded successfully and a subsequent wrapper
  /// or inline ad load has timed out.
  kIMAVastLoadTimeout = 3001,
  /// At least one VAST wrapper loaded and a subsequent wrapper or inline ad
  /// load has resulted in a 404 response code.
  kIMAVastInvalidUrl = 3002,
  /// The ad response was not recognized as a valid VAST ad.
  kIMAVastMalformedResponse = 3003,
  /// A media file of a VAST ad failed to load or was interrupted mid-stream.
  kIMAVastMediaError = 3004,
  /// The maximum number of VAST wrapper redirects has been reached.
  kIMAVastTooManyRedirects = 3005,
  /// Assets were found in the VAST ad response, but none of them matched the
  /// video player's capabilities.
  kIMAVastAssetMismatch = 3006,
  /// No assets were found in the VAST ad response.
  kIMAVastAssetNotFound = 3007,
  /// Invalid arguments were provided to SDK methods.
  kIMAInvalidArguments = 3101,
  /// A companion ad failed to load or render.
  kIMACompanionAdLoadingFailed = 3102,
  /// The ad response was not understood and cannot be parsed.
  kIMAUnknownAdResponse = 3103,
  /// An unexpected error occurred while loading the ad.
  kIMAUnexpectedLoadingError = 3104,
  /// An overlay ad failed to load.
  kIMAOverlayAdLoadingFailed = 3105,
  /// An overlay ad failed to render.
  kIMAOverlayAdPlayingFailed = 3106,
} IMAErrorCode;

#pragma mark -

/// Surfaces an error that occured during ad loading or playing.
@interface IMAAdError : NSError

/// The |errorType| accessor provides information about whether the error
/// occured during ad loading or ad playing.
@property (nonatomic, readonly) IMAErrorType errorType;

@end
