//
//  VideoUtils.m
//  CustomUIControlsApp
//
//  Created by Tom Abbott on 2/6/13.
//  Copyright (c) 2013 Tom Abbott. All rights reserved.
//

#import "VideoUtils.h"

@implementation VideoUtils

+ (NSString *)makeTimeReadable:(NSTimeInterval)time
{
    if (time < 1)
    {
        return @"00:00";
    }
    
    NSInteger hours = floor(time / 60.0f / 60.0f);
    NSInteger minutes = (NSInteger)(time / 60.0f) % 60;
    NSInteger seconds = (NSInteger)time % 60;
    
    NSString *ret;
    if (hours > 0)
    {
        ret = [NSString stringWithFormat:@"%d:%.2d:%.2d", hours, minutes, seconds];
    }
    else
    {
        ret = [NSString stringWithFormat:@"%.2d:%.2d", minutes, seconds];
    }
    
    return ret;
}

@end
