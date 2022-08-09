//
//  ALPSRange.h
//  ALPSiOS
//
//  Created by Patrick Lazik on 7/27/21.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ALPSBeacon;

@interface ALPSRange : NSObject

@property (nonatomic) double timeStamp;
@property (nonatomic) float range;
@property (nonatomic) float rssi;
@property (nonatomic) NSUInteger slot;
@property (nonatomic) NSUInteger chirpIdx;
@property (strong, nonatomic) ALPSBeacon *beacon;

-(id) initWithRange:(float)range rssi:(float)rssi slot:(NSUInteger)slot chirpIdx:(NSUInteger)chirpIdx timeStamp:(double)timeStamp;

@end

NS_ASSUME_NONNULL_END
