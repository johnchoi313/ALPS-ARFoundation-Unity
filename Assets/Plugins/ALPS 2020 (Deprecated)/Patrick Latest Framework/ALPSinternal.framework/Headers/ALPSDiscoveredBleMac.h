//
//  ALPSDiscoveredBleMac.h
//  alps-framework-objc
//
//  Created by Nick Wilkerson on 3/11/18.
//  Copyright © 2018 Yodel Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ALPSDiscoveredBleMac : NSObject

-(id)initWithBleMac:(NSString *)bleMac date:(NSDate *)date;

@property (nonatomic) NSString *bleMac;
@property (nonatomic) NSNumber *slot;
@property (nonatomic) NSDate *date;
@property (nonatomic) CGPoint location;

@end
