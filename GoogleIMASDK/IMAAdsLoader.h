//
//  IMAAdsLoader.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMAAdsManager.h"
#import "IMAAdsRequest.h"
#import "IMAAdError.h"

#pragma mark IMAAdsLoadedData

/// Ad loaded data that is returned when the adsLoader loads the ad.
@interface IMAAdsLoadedData : NSObject

/// The ads manager returned by the adsLoader.
@property(nonatomic, retain) IMAAdsManager *adsManager;
/// Other user context object returned by the adsLoader.
@property(nonatomic, retain) id userContext;

@end

#pragma mark -
#pragma mark IMAAdLoadingErrorData

/// Ad error data that is returned when the adsLoader failed to load the ad.
@interface IMAAdLoadingErrorData : NSObject

/// The ad error that occured while loading the ad.
@property(nonatomic, retain) IMAAdError *adError;
/// Other user context object returned by the adsLoader.
@property(nonatomic, retain) id userContext;

@end

#pragma mark -
#pragma mark IMAAdsLoaderDelegate

@class IMAAdsLoader;

/// Delegate object that receives state change callbacks from IMAAdsLoader.
@protocol IMAAdsLoaderDelegate<NSObject>

/// Called when ads are successfully loaded from the ad servers by the loader.
- (void)adsLoader:(IMAAdsLoader *)loader
    adsLoadedWithData:(IMAAdsLoadedData *)adsLoadedData;

/// Error reported by the ads loader when ads loading failed.
- (void)adsLoader:(IMAAdsLoader *)loader
    failedWithErrorData:(IMAAdLoadingErrorData *)adErrorData;

@end

#pragma mark -

/// The IMAAdsLoader class allows requesting ads from various ad servers.
//
/// To do so, IMAAdsLoaderDelegate must be implemented and then ads should
/// be requested.
@interface IMAAdsLoader : NSObject

/// Request ads by providing the ads |request| object with properties populated
/// with parameters to make an ad request to Google or DoubleClick ad server.
/// Optionally, |userContext| object that is associated with the ads request can
/// be provided. This can be retrieved when the ads are loaded.
- (void)requestAdsWithRequestObject:(IMAAdsRequest *)request
                        userContext:(id)context;

/// Request ads from a adsserver by providing the ads request object.
- (void)requestAdsWithRequestObject:(IMAAdsRequest *)request;

/// Delegate object that receives state change notifications from this
/// IMAAdsLoader. Remember to nil the delegate before releasing this
/// object.
@property(nonatomic, assign) NSObject<IMAAdsLoaderDelegate> *delegate;

@end
