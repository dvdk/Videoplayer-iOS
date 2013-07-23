//
//  VideoUtils.h
//  CustomUIControlsApp
//
//  Created by Tom Abbott on 2/6/13.
//  Copyright (c) 2013 Tom Abbott. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VideoUtils : NSObject 

/**
 *Utility method for making a @NSTimeInterval readable
 *
 *@param time The @NSTimeInterval that you want to make readable in the format of 00:00
 *@return Returns the readable time in the format of 00:00
 */
+ (NSString *)makeTimeReadable:(NSTimeInterval)time;

@end
