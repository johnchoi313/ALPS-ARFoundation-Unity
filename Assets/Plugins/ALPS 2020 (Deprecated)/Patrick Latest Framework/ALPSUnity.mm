//
//  ALPSUnity.m
//  alps-framework-objc
//
//  Created by Patrick Lazik on 11/27/19.
//  Copyright © 2019 Yodel Labs. All rights reserved.
//

#import "ALPSUnity.h"
#import <ALPSinternal/ALPSinternal.h>
#import <ARKit/ARKit.h>

float currLocation[3];
float currLocationStdDev[4];
float currTransform[4];
ALPSLocationManager *locationManager;

@interface ALPSUnity () <ALPSLocationManagerDelegate> {
    
}

@end
@implementation ALPSUnity

-(id)initWithRemoteRealmIdentifier:(NSString *)remoteRealmIdentifier {
    // Initialize location manager and set us as the delegate
    locationManager = [[ALPSLocationManager alloc] initWithRemoteRealmIdentifier:remoteRealmIdentifier useRelativeLocation:YES solveIn3D:YES];
    locationManager.delegate = self;
    [locationManager startUpdatingLocation];
    return self;
}

// Location manager delegate method, called whenever a new location/transform is available
-(void)locationManager:(ALPSLocationManager *)manager
     didUpdateLocation:(ALPSLocation3D)location
      andPoseTransform:(ALPSPoseTransform)poseTransform
           fromBeacons:(NSArray<ALPSRangeDataPoint*>*)rangeDataPoints
             timeStamp:(double)timeStamp {
    // Store location and transform in local variables
    @synchronized (locationManager) {
        currLocation[0] = location.x;
        currLocation[1] = location.y;
        currLocation[2] = location.z;
        
        currLocationStdDev[0] = poseTransform.xStdDev;
        currLocationStdDev[1] = poseTransform.yStdDev;
        currLocationStdDev[2] = poseTransform.zStdDev;
        currLocationStdDev[3] = poseTransform.rotationStdDev;
        
        currTransform[0] = poseTransform.x;
        currTransform[1] = poseTransform.y;
        currTransform[2] = poseTransform.z;
        currTransform[3] = poseTransform.rotation;
    }
}

-(void) fuseRelativeLocationWithX:(float) x y:(float)y locZ:(float)z eulerX:(float)eulerX eulerY:(float)eulerY eulerZ:(float)eulerZ timeStamp:(NSTimeInterval)timeStamp{
    // Send ARKit location and orientation data to ALPS
    [locationManager fuseRelativeLocationWithX:x y:y z:z eulerX:eulerX eulerY:eulerY eulerZ:eulerZ timeStamp:timeStamp];
}

-(void) setCameraTrackingState:(ARCamera*) camera API_AVAILABLE(ios(11.0)){
    // Tell ALPS about the tracking state of ARKit
       switch (camera.trackingState) {
           case ARTrackingStateNormal:
               locationManager.trackingState = ALPSTrackingStateNormal;
               break;
              
           case ARTrackingStateLimited:
               switch(camera.trackingStateReason){
                   case ARTrackingStateReasonNone:
                       locationManager.trackingState = ALPSTrackingStateNotAvailable;
                       break;
                   case ARTrackingStateReasonInitializing:
                       locationManager.trackingState = ALPSTrackingStateInitializing;
                       break;
                   case ARTrackingStateReasonInsufficientFeatures:
                       locationManager.trackingState = ALPSTrackingStateInsufficientFeatures;
                       break;
                      
                   case ARTrackingStateReasonExcessiveMotion:
                       locationManager.trackingState = ALPSTrackingStateExcessiveMotion;
                       break;
                   case ARTrackingStateReasonRelocalizing:
                       locationManager.trackingState = ALPSTrackingStateRelocalizing;
                       break;
               }
               break;
           case ARTrackingStateNotAvailable:
               locationManager.trackingState = ALPSTrackingStateNotAvailable;
               break;
       }
}
@end

extern "C" {
    
    void _startUpdatingLocation(){
        [locationManager startUpdatingLocation];
    }
    void _stopUpdatingLocation(){
        [locationManager stopUpdatingLocation];
    }
    
    void _getLocationAndTransform (float *locX, float *locY, float *locZ, float *transX, float *transY, float* transZ, float* transYaw, float* stdDevX, float* stdDevY, float* stdDevZ, float* stdDevYaw)
    {
        // Get location and transform from local variables
        @synchronized (locationManager) {
            *locX = currLocation[0];
            *locY = currLocation[1];
            *locZ = currLocation[2];
            
            *transX = currTransform[0];
            *transY = currTransform[1];
            *transZ = currTransform[2];
            *transYaw = currTransform[3];
            
            *stdDevX = currLocationStdDev[0];
            *stdDevY = currLocationStdDev[1];
            *stdDevZ = currLocationStdDev[2];
            *stdDevYaw = currLocationStdDev[3];
        }
    }
}


