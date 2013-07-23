//
//  BCKIMAConstants.h
//  IOSContainer
//
//  Created by Erik Price on 2013 04 29.
//  Copyright (c) 2013 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>


// >>>>>>>>>>>>>>>>>>>>>> TODO - document when these events are or should be dispatched and their payloads

extern NSString * const kBCKIMAEventAdCuePoint;
extern NSString * const kBCKIMAEventRequestAdCuePoints;
extern NSString * const kBCKIMAEventRequestIMAAdsRequest;
extern NSString * const kBCKIMAEventRespondIMAAdsRequest;
extern NSString * const kBCKIMAEventPlayAd;

extern NSString * const kBCKIMAEventDidConfigure;
extern NSString * const kBCKIMAEventDidFailAds;
extern NSString * const kBCKIMAEventDidLoadAds;
extern NSString * const kBCKIMAEventDidClickTrackingViewReceiveTouch;
extern NSString * const kBCKIMAEventDidFinishAdRoll;
extern NSString * const kBCKIMAEventDidRequestContentPause;
extern NSString * const kBCKIMAEventDidRequestContentResume;
extern NSString * const kBCKIMAEventDidReportAdError;

extern NSString * const kBCKIMAEventKeyVideo;
extern NSString * const kBCKIMAEventKeyAdCuePoints;
extern NSString * const kBCKIMAEventKeyCurrentCuePoints;
extern NSString * const kBCKIMAEventKeyIMAAdRequests;
extern NSString * const kBCKIMAEventKeyAdsLoadedData;
extern NSString * const kBCKIMAEventKeyAdsLoader;
extern NSString * const kBCKIMAEventKeyAdLoadingErrorData;
extern NSString * const kBCKIMAEventKeyClickTrackingView;
extern NSString * const kBCKIMAEventKeyClickTrackingViewTouchEvent;
extern NSString * const kBCKIMAEventKeyAdsManager;
extern NSString * const kBCKIMAEventKeyAdError;
extern NSString * const kBCKIMAEventKeyDidFinishAdRollCuePoints;