//
//  BCEventLogger.h
//  BCiOSLibrary
//
//  Created by  on 5/31/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCComponent.h"

@interface BCEventLogger : BCComponent

@property (nonatomic, copy) NSString *loggingPrefix;
/**
 * If true, log event details along with event types.
 */
@property (nonatomic) BOOL verbose;

- (void)startLogging;
- (void)stopLogging;

@end
