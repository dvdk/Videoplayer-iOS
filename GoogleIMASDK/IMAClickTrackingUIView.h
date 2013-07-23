//
//  IMAClickTrackingUIView.h
//  Google IMA SDK
//
//  Declares IMAClickTrackingUIView instance that is set to track clicks on the
//  ad. Also defines a delegate protocol for click tracking view to get
//  clicks from the view.
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#pragma mark IMAClickTrackingUIViewDelegate

@class IMAClickTrackingUIView;

/// Delegate protocol for IMAClickTrackingUIView.
//
/// The publisher can adopt this protocol to receive touch events from the
/// IMAClickTrackingUIView instance.
@protocol IMAClickTrackingUIViewDelegate

 @required
/// Received when the user touched the click tracking view.
- (void)clickTrackingView:(IMAClickTrackingUIView *)view
    didReceiveTouchEvent:(UIEvent *)event;

@end

#pragma mark -

/// A UIView instance that is used as the click tracking element.
//
/// In order for the SDK to track clicks on the ad, a transparent click tracking
/// should be added on the video player and should be added as the tracking
/// element by setting click tracking view on IMAVideoAdsManager.
@interface IMAClickTrackingUIView : UIView

/// Delegate object that receives touch notifications.
//
/// The caller should implement IMAClickTrackingUIViewDelegate to get touch
/// events from the view. Remember to nil the delegate before deallocating
/// this object.
@property (nonatomic, assign) id<IMAClickTrackingUIViewDelegate> delegate;

@end
