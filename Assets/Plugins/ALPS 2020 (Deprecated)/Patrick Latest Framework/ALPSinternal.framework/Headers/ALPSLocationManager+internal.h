//
//  ALPSLocationManager+internal.h
//  alps-framework-objc
//
//  Created by Nick Wilkerson on 8/15/18.
//  Copyright © 2018 Yodel Labs. All rights reserved.
//

#import "ALPSLocationManager.h"
#import "BLETimeSyncState.h"
#import "ALPSBeaconInfo.h"
#import "ALPSDiscoveredBleMac.h"


@protocol ALPSLocationManagerDebugDelegate <ALPSLocationManagerDelegate>

/*
 *  Provides information on BLE time sync state
 */
-(void)locationManager:(ALPSLocationManager *)manager
     didChangeBLEState:(BLETimeSyncState)state;

/*
 *  Provides raw range values before the solver
 */
-(void)locationManager:(ALPSLocationManager *)manager
      didReceiveRanges:(NSArray<ALPSRangeDataPoint *> *)rangeDataArray;


/*
 *  Provides range range values as they come in
 */
-(void)locationManager:(ALPSLocationManager *)manager
       didReceiveRange:(ALPSRangeDataPoint *)range;

/*
 *  Provides the BLE Mac of a newly discovered beacon
 */
-(void)locationManager:(ALPSLocationManager *)manager
didDiscoverBeaconWithBleMac:(NSString *)bleMac rssi:(NSInteger)rssi;

/*
 *  Provides the array of beacons that are used for solving.  The array will only contain beacons that have been seen and beacons near beacons that have been seen.
 *  Beacons will disappear from this array as they time out.
 */
-(void)locationManager:(ALPSLocationManager *)manager
didChangeDiscoveredBeaconArray:(NSArray<ALPSDiscoveredBleMac*> *)beaconBleArray;

-(void)locationManager:(ALPSLocationManager *)locationManager didReceiveTimeSyncPacketWithData:(NSData *)data rssi:(NSInteger)rssi timeStamp:(double)timeStamp;

-(void)locationManager:(ALPSLocationManager *)locationManager didUpdateParticleImage:(UIImage *)particleImage;

@end


@interface ALPSLocationManager () {
    
}

@property id<ALPSLocationManagerDebugDelegate> debugDelegate;

@property (nonatomic, retain) NSArray<ALPSBeaconInfo *> *allBeacons;

@end
