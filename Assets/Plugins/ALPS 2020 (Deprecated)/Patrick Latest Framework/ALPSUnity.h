//
//  ALPSUnity.h
//  alps-framework-objc
//
//  Created by Patrick Lazik on 11/27/19.
//  Copyright © 2019 Yodel Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ALPSLocationManager, ARCamera;
@interface ALPSUnity : NSObject

// Initialize ALPS with Remote Realm Identifier (for loading map/beacon data)
-(id)initWithRemoteRealmIdentifier:(NSString *)remoteRealmIdentifier;
-(void) fuseRelativeLocationWithX:(float) x y:(float)y locZ:(float)z eulerX:(float)eulerX eulerY:(float)eulerY eulerZ:(float)eulerZ timeStamp:(NSTimeInterval)timeStamp;

-(void) setCameraTrackingState:(ARCamera*) camera;

@end


extern "C" {

// Start updating location using ALPS
void _startUpdatingLocation();

// Stop updating location using ALPS
void _stopUpdatingLocation();

// Get the most recent location, transform and condidence values
void _getLocationAndTransform (float *locX, float *locY, float *locZ, float *transX, float *transY, float* transZ, float* transYaw, float* stdDevX, float* stdDevY, float* stdDevZ, float* stdDevYaw);
}
