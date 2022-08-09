/******************************************************************************
 *  ALPS, The Acoustic Location Processing System.
 *  Copyright (C) 2017, Yodel Labs
 *  All rights reserved.
 *
 *  This software is the property of Yodel Labs. Source may
 *  be modified, but this license does not allow distribution.  Binaries built
 *  for research purposes may be freely distributed, but must acknowledge
 *  Yodel Labs.  No other use or distribution can be made
 *  without the written permission of the authors and Yodel Labs.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  Contributing Author(s):
 *  Patrick Lazik
 *  Nick Wilkerson
 *
 *******************************************************************************/

#import <Foundation/Foundation.h>

@interface ALPSBeaconInfo : NSObject

-(id)initWithBeaconBleMac:(NSString *)beaconBleMac fifteenFourMac:(NSString *)fifteenFourMac slotNumber:(NSInteger)beaconSlotNumber x:(double)x y:(double)y z:(double)z;

@property (nonatomic, readonly) NSString *beaconBleMac;
@property (nonatomic, readonly) NSString *beaconFifteenFourMac;
@property (nonatomic, readonly) NSInteger beaconSlotNumber;
@property (nonatomic, readonly) double x;
@property (nonatomic, readonly) double y;
@property (nonatomic, readonly) double z;

@end
