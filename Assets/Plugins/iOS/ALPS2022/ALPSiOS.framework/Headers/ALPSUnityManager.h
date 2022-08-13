//
//  ALPSUnityManager.m
//  ALPSiOS
//
//  Created by Patrick Lazik on 8/5/22.
//  Copyright © 2022 Yodel Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ALPS_USERNAME @"ETC"
#define ALPS_PASSWORD @"etcdemo123"

@interface ALPSUnityManager : NSObject

/**
 * Method to initialize the signleton ALPSUnityManager obtain a reference to it. The ALPSUnityManager will only be able to localize in areas that exist in the ALPS Web Portal.
 * @param username Your username to the ALPS Web Portal.
 * @param password Your password to the ALPS Web Portal.
 * @returns Reference to the signelton ALPSUnityManager.
 */
+(id)sharedManagerWithUsername:(NSString*)username password:(NSString*)password;

/**
 * Method to supply VIO pose from ARKit to ALPS. This should be called whenever Unity has a pose update.
 * @param x x pose coordinate from ARKit
 * @param y y pose coordinate from ARKit
 * @param z z pose coordinate from ARKit
 * @param eulerX eulerX pose angle from ARKit
 * @param eulerY eulerY pose angle from ARKit
 * @param eulerZ eulerZ pose angle from ARKit
 */
-(void) updateARPoseWithX:(float)x y:(float)y z:(float)z eulerX:(float)eulerX eulerY:(float)eulerY eulerZ:(float)eulerZ;

@end

/* ----- METHODS TO BE CALLED FROM UNITY ----- */
extern "C" {

void _init();

void _updateARPose(float x, float y, float z, float eulerX, float eulerY, float eulerZ);

/**
 * Method to start receiving location and transform updates from ALPS. This should be run after initializing the ALPSUnityManager using sharedManagerWithUsername()
 */
void _startUpdatingLocation();

/**
 * Method to stop receiving location and transform updates from ALPS.
 */
void _stopUpdatingLocation();

/**
 * Method to get the current location, location and rotation accuracy and AR transform data.
 * @param location pointer to an array of floats of length 3. The current location of the device as determined by ALPS will be copied into this array as [x, y, z]
 * @param locationAccuracy pointer to an array of floats of length 4. The accuracy of the location and rotation of the device in meters as determined by ALPS will be copied into this array as [accuracyX, accuracyY, accuracyZ, accuracyRotation]
 * @param transform pointer to an array of floats of length 16. The current 3D 4x4 transformation matrix to transform ARKit's frame of reference to ALPS' frame of reference will be copied into this array as a flattened SCNMatrix4 (see https://developer.apple.com/documentation/scenekit/scnmatrix4?language=objc). The SCNMatrix4 elements are copied into the array in the following order [m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44].
 */
void _getLocationAndTransform (float *location, float *locationAccuracy, float *transform);
}
