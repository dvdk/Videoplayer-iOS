//
//  BCSDKCatalog.h
//  CatalogPlaylistApp
//
//  Created by Tom Abbott on 4/11/13.
//  Copyright (c) 2013 brightcove. All rights reserved.
//

#import "BCCatalog.h"

@interface BCSDKCatalog : BCCatalog


- (id)initWithToken:(NSString *)token baseURL:(NSString *)baseURL iu:(NSString *) iu;

@end
