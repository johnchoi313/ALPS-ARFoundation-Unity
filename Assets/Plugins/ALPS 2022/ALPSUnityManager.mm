//
//  ALPSUnityManager.m
//  ALPSiOS
//
//  Created by Patrick Lazik on 8/5/22.
//  Copyright © 2022 Yodel Labs. All rights reserved.
//

#import "ALPSUnityManager.h"
#import "ALPSLocationManager.h"
#import "ALPSLocation.h"
#import <ARKit/ARKit.h>

float currLocation[3];
float currLocationStdDev[4];
float currTransform[16];
ALPSLocationManager *locationManager;

@interface ALPSUnityManager () <ALPSLocationManagerDelegate> {
}

-(id)initWithUsername:(NSString*)username password:(NSString*)password;

@end
@implementation ALPSUnityManager

static ALPSUnityManager *sharedUnityManager = nil;

+(id)sharedManagerWithUsername:(NSString*)username password:(NSString*)password{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedUnityManager = [[self alloc] initWithUsername:username password:password];
    });
    return sharedUnityManager;
}

-(id)initWithUsername:(NSString*)username password:(NSString*)password{
    self = [super init];
    if(self){
        locationManager = [ALPSLocationManager sharedManagerWithUsername:username password:password doRecordData:NO];
    }
    return [self init];
}

- (void)alpsLocationManager:(ALPSLocationManager *)locationManager didUpdateLocation:(ALPSLocation *)location poseTransform:(SCNMatrix4)poseTransform poseTransformAccuracy:(ALPSPoseTransformAccuracy)poseTransformAccuracy{
    // Store location and transform in local variables
    @synchronized (locationManager) {
        currLocation[0] = location.x;
        currLocation[1] = location.y;
        currLocation[2] = location.z;
        
        currLocationStdDev[0] = poseTransformAccuracy.xStdDev;
        currLocationStdDev[1] = poseTransformAccuracy.yStdDev;
        currLocationStdDev[2] = poseTransformAccuracy.zStdDev;
        currLocationStdDev[3] = poseTransformAccuracy.rotationStdDev;
        
        currTransform[0] = poseTransform.m11;
        currTransform[1] = poseTransform.m12;
        currTransform[2] = poseTransform.m13;
        currTransform[3] = poseTransform.m14;
        currTransform[4] = poseTransform.m21;
        currTransform[5] = poseTransform.m22;
        currTransform[6] = poseTransform.m23;
        currTransform[7] = poseTransform.m24;
        currTransform[8] = poseTransform.m31;
        currTransform[9] = poseTransform.m32;
        currTransform[10] = poseTransform.m33;
        currTransform[11] = poseTransform.m34;
        currTransform[12] = poseTransform.m41;
        currTransform[13] = poseTransform.m42;
        currTransform[14] = poseTransform.m43;
        currTransform[15] = poseTransform.m44;
    }
}

-(void) updateARPoseWithX:(float)x y:(float)y z:(float)z eulerX:(float)eulerX eulerY:(float)eulerY eulerZ:(float)eulerZ{
    // Send ARKit location and orientation data to ALPS
    [locationManager updateARPoseWithX:x y:y z:z eulerX:eulerX eulerY:eulerY eulerZ:eulerZ];
}

extern "C" {
    
    void _init(char *username, char *password){
        [ALPSUnityManager sharedManagerWithUsername:[NSString stringWithUTF8String: username] password:[NSString stringWithUTF8String: password]];
    }
    
    void _startUpdatingLocation(){
        [locationManager startUpdatingLocation];
    }
    void _stopUpdatingLocation(){
        [locationManager stopUpdatingLocation];
    }
    
    void _updateARPose(float x, float y, float z, float eulerX, float eulerY, float eulerZ){
        [sharedUnityManager updateARPoseWithX:x y:y z:z eulerX:eulerX eulerY:eulerY eulerZ:eulerZ];
    }
    
    void _getLocationAndTransform (float *location, float *locationAccuracy, float *transform)
    {
        // Get location and transform from local variables
        @synchronized (locationManager) {
            memcpy(location, currLocation, sizeof(currLocation));
            memcpy(locationAccuracy, currLocationStdDev, sizeof(currLocationStdDev));
            memcpy(transform, currTransform, sizeof(currTransform));
        }
    }
}

@end
