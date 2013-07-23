//
//  BCKIMAPlugin.h
//  IOSContainer
//
//  Created by Erik Price on 2013 04 02.
//  Copyright (c) 2013 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMAAdsLoader.h"
#import "IMAClickThroughBrowser.h"
#import "IMAClickTrackingUIView.h"
#import "IMAVideoAdsManager.h"


@protocol BCEventEmitterProtocol;

@class BCVideo;


@interface BCKIMAPlugin : NSObject <IMAAdsLoaderDelegate, IMAClickTrackingUIViewDelegate, IMAVideoAdsManagerDelegate>

@property (nonatomic, retain, readonly) UIView *adContainer;
@property (nonatomic, retain) AVPlayer *adPlayer;
@property (nonatomic, retain) AVPlayerLayer *adPlayerLayer;
@property (nonatomic, copy) NSArray *(^adPolicy)(BCVideo *);
@property (nonatomic, retain, readonly) IMAAdsLoader *adsLoader;
@property (nonatomic, retain, readonly) IMAVideoAdsManager *adsManager;

// The `clickTrackingView` will be automatically set when this BCKIMAPlugin
// instance is configured, unless it is set explicitly beforehand. Setting it
// explicitly means that the `kBCKIMAEventDidClickTrackingViewReceiveTouch`
// will not be emitted on the emitter automatically. Wait for the
// `kBCKIMAEventDidConfigure` event prior to accessing this property if using
// the implicitly-set instance.
@property (nonatomic, retain) IMAClickTrackingUIView *clickTrackingView;
@property (nonatomic, retain, readonly) id<BCEventEmitterProtocol> emitter;

- (id)initWithEmitter:(id<BCEventEmitterProtocol>)emitter adContainer:(UIView *)adContainer;
- (void)configure;

@end