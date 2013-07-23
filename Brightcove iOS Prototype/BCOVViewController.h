//
//  BCOVViewController.h
//  BrightcoveIMASamplePreMid
//
//  Created by Tom Abbott on 7/3/13.
//  Copyright (c) 2013 Brightcove. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IMAClickThroughBrowser.h"

@class BCQueuePlayer;
@class BCUIControls;
@class BCKIMAPlugin;
@class IMAClickTrackingUIView;
@class EmulatedControls;

@interface BCOVViewController : UIViewController <IMAClickThroughBrowserDelegate>

@property (strong, nonatomic) IBOutlet UIView *playerView;
@property (strong, nonatomic) IBOutlet UIView *adView;
@property (strong, nonatomic) IBOutlet UIButton *clickTrackingButton;

@property (strong, nonatomic) BCQueuePlayer *player;
@property (strong, nonatomic) BCKIMAPlugin *imaPlugin;
@property (strong, nonatomic) EmulatedControls *controls;

- (void) configurePlayer:(NSArray *)videos;
@end
