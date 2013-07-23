//
//  IMAAdsRequest.h
//  GoogleIMA
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Base class for all ads request objects.
//
/// Caller can provide ads request key and values that needs to be passed to
/// IMAAdsLoader to request ads.
@interface IMAAdsRequest : NSObject

/// Set a string request parameter value for a key.
- (void)setRequestParameterValue:(NSString *)value forKey:(NSString *)key;

/// Get a string request parameter given a key.
- (NSString *)getRequestParameterValueForKey:(NSString *)key;

/// Set the companions slots that need to be filled.
- (void)setCompanionSlots:(NSArray *)companionSlots;

@end
