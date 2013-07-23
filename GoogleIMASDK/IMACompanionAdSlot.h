//
//  IMACompanionAdSlot.h
//  GoogleIMA
//
//  Copyright 2012 Google Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

///  Ad slot for companion ads.  The SDK will put a subview inside the provided
///  UIView container.  The companion will be matched to the width and height
///  provided here.
@interface IMACompanionAdSlot : NSObject

@property(nonatomic, retain) UIView *container;

@property(nonatomic) float width;
@property(nonatomic) float height;

- (IMACompanionAdSlot *)initWithContainer:(UIView *)container
                                          width:(float)width
                                         height:(float)height;

@end
