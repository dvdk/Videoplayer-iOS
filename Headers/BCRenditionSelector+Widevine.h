//
//  BCWidevineRenditionSelector.h
//  WidevinePlugin
//
//  Created by David McGaffin on 9/17/12.
//
//

#import "BCRenditionSelector.h"

@interface BCRenditionSelector (Widevine)

+ (BOOL)isWidevineRendition:(NSString *)url;

@end
