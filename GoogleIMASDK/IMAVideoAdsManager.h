//
//  IMAVideoAdsManager.h
//  Google IMA SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//
//  Declares IMAVideoAdsManager interface that manages playing and unloading
//  video ads.

#import <AVFoundation/AVFoundation.h>
#import "IMAAdError.h"
#import "IMAAdsManager.h"
#import "IMAClickTrackingUIView.h"

#pragma mark IMAVideoAdsManagerDelegate

@class IMAVideoAdsManager;

/// Delegate object that gets state change callbacks from IMAVideoAdsManager.
@protocol IMAVideoAdsManagerDelegate<NSObject>

/// Called when content should be paused. This usually happens right before a
/// an ad is about to cover the content.
- (void)contentPauseRequested:(IMAVideoAdsManager *)adsManager;

/// Called when content should be resumed. This usually happens when ad ad
/// finishes or collapses.
- (void)contentResumeRequested:(IMAVideoAdsManager *)adsManager;

@optional
/// Called when an error occured while loading or playing the ad.
- (void)didReportAdError:(IMAAdError *)error;

@end

#pragma mark -

#pragma mark IMAVastEventNotifications
/// \memberof IMAVideoAdsManager
/// Start Vast event broadcasted by the ads manager.
//
/// This happens when video ad starts to play.
extern NSString * const IMAVastEventStartNotification;

/// \memberof IMAVideoAdsManager
/// First quartile Vast event broadcasted by the ads manager.
//
/// This happens when ad crosses first quartile boundary.
extern NSString * const IMAVastEventFirstQuartileNotification;

/// \memberof IMAVideoAdsManager
/// Midpoint Vast event broadcasted by the ads manager.
//
/// This happens when ad crosses midpoint boundary.
extern NSString * const IMAVastEventMidpointNotification;

/// \memberof IMAVideoAdsManager
/// Third quartile Vast event broadcasted by the ads manager.
//
/// This happens when ad crosses third quartile boundary.
extern NSString * const IMAVastEventThirdQuartileNotification;

/// \memberof IMAVideoAdsManager
/// Complete Vast event broadcasted by the ads manager.
//
/// This happens when video ad completes playing successfully.
extern NSString * const IMAVastEventCompleteNotification;

/// \memberof IMAVideoAdsManager
/// Pause Vast event broadcasted by the Video ads manager.
//
/// This happens when video ad pauses.
extern NSString * const IMAVastEventPauseNotification;

/// \memberof IMAVideoAdsManager
/// Click event broadcasted by the Video ads manager.
//
/// This happens when user clicks on the click tracking element overlayed on
/// the video ad.
extern NSString * const IMAVastEventClickNotification;

/// \memberof IMAVideoAdsManager
/// Rewind event broadcasted by the Video ads manager.
//
/// This happens when user rewinds the video ad.
extern NSString * const IMAVastEventRewindNotification;

/// \memberof IMAVideoAdsManager
/// Skip event broadcast by the Video ads manager.
//
/// This happens when user skips the current ad.
extern NSString * const IMAVastEventSkipNotification;

#pragma mark -

/// The IMAVideoAdsManager class is responsible for playing video ads.
@interface IMAVideoAdsManager : IMAAdsManager

/// Play the loaded ad in the provided |player|.
//
/// The caller should implement IMAVideoAdsManagerDelegate and set the delegate
/// before calling this method so the SDK can send notifications about state
/// changes that require player attention.

- (void)playWithAVPlayer:(AVPlayer *)player;

/// Sets the click tracking view which will tracks clicks on the player.
//
/// Click tracking must be enabled on the video player area before the ad can be
/// played. Create an instance that is of type IMAClickTrackingUIView and set it
/// as a transparent view on top of the video player. If this is not set clicks
/// will not be tracked by the SDK.
@property(nonatomic, retain) IMAClickTrackingUIView *clickTrackingView;

/// Delegate object that receives state change notifications.
//
/// The caller should implement IMAVideoAdsManagerDelegate to get state change
/// notifications from the ads manager. Remember to nil the delegate before
/// deallocating this object.
@property(nonatomic, assign) NSObject<IMAVideoAdsManagerDelegate> *delegate;

@end
