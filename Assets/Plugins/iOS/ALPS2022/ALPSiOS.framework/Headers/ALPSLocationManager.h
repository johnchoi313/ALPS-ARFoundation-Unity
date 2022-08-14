/******************************************************************************
 *  ALPS, The Acoustic Local Positioning System.
 *  ALPSLocationManager
 *  Yodel Labs, 2021
 *
 *  Contributing Author(s):
 *  Patrick Lazik
 *
 *******************************************************************************/

/**
 *  Location Manager class to interface with ALPS. This is the main class to interface with ALPS and allows for ALPS Location Services to be started and stopped. It reports  back the current location of the device and various system state change events through the ALPSLocationManagerDelegate protocol.
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "MGLLocationManager.h"

#define GEO_LOCATION_SCALE 10 /**< Geodesic  */

NS_ASSUME_NONNULL_BEGIN

/**
 * Accuracy values for the pose transform from ARKit to ALPS.
 * These values represent the current standard deviation of location measurement estimates in various axes.
 * Lower values indicate higher accuracy.
 */
typedef struct ALPSPoseTransformAccuracy {
    float xStdDev;  /**< Standard deviation of location estimates along the x axis in meters */
    float yStdDev;  /**< Standard deviation of location estimates along the y axis in meters */
    float zStdDev;  /**< Standard deviation of location estimates along the z axis in meters */
    float rotationStdDev; /**< Standard deviation of yaw orientation estimates in radians */
} ALPSPoseTransformAccuracy;


typedef struct SCNMatrix4 SCNMatrix4;
@class ALPSLocationManager, ALPSRange, ALPSBLEManager, ALPSAudioManager, ALPSFloor, ALPSLocation, ARFrame, ARSession, ARCamera;

/**
 * ALPSLocationManagerDelegate protocol for receiving the current location of the device and various system state change events.
 */
@protocol ALPSLocationManagerDelegate <MGLLocationManagerDelegate>
@optional

/**
 * Delegate method for receiving changes in BLE synchronization state.
 * @param locationManager A pointer to the ALPSLocationManager object that is calling this method.
 * @param isSynced is YES if BLE is synced and NO if it is not synced. BLE needs to be synced for ranging and localization to be performed.
 * @param timeStamp time when BLE was synced or desynced. Expressed in seconds since boot time of the device (monotonic clock).
 */
-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didChangeBLESyncState:(BOOL)isSynced timeStamp:(double)timeStamp;

/**
 * Delegate method for receiving beacon discovery notificactions via BLE. Before localization can be performed ALPS finds its rough location using BLE. This delegate method is usually used for debugging purposes.
 * @param locationManager A pointer to the ALPSLocationManager object that is calling this method.
 * @param macAddress BLE MAC address of the beacon or base station that was discovered.
 * @param rssi Received Signal Strenght Indicator (RSSI) value of the signal received from the beacon that was discovered in dBm.
 * @param timeStamp time when beacon was discovered. Expressed in seconds since boot time of the device (monotonic clock).
 * @param isBeacon Yes if the discovered device is a beacon, no if it is a base station
 */
-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didDiscoverDeviceWithMACAddress:(NSString *)macAddress rssi:(NSInteger)rssi timeStamp:(double)timeStamp isBeacon:(BOOL)isBeacon;

/**
 * Delegate method for receiving ultrasound range measurements from beacons to this device.
 * @param locationManager A pointer to the ALPSLocationManager object that is calling this method.
 * @param range An ALPSRange object containing the measured range from a particular beacon to this device at a certain point in time.
 */
-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didReceiveRange:(ALPSRange*)range;

/**
 * Delegate method for receiving updates to the current floor that this device is located on. This is called when the floor the device is located on is first determined, as well as when the device moves to a different floor.
 * @param locationManager A pointer to the ALPSLocationManager object that is calling this method.
 * @param floor An ALPSFloor object containing information about the current floor the device is located on. This information is sourced from the ALPS Web Portal that contains this floor.
 */
-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didUpdateFloor:(ALPSFloor*)floor;

/**
 * Delegate method for receiving location updates of this device.
 * @param locationManager A pointer to the ALPSLocationManager object that is calling this method.
 * @param location An ALPSLocation object containing the current estimated location and accuracy of this device in the ALPS reference frame and a timestamp of when this location was estimated.
 * @param poseTransform The transformation matrix between ARKit's reference frame and ALPS'. This transform can be applied to SceneKit/SpriteKit and ARKit related objects to transform them to the global ALPS coordinate system.
 * @param poseTransformAccuracy A struct containing the estimated accuracy of the poseTransform.
 */
-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didUpdateLocation:(ALPSLocation*)location poseTransform:(SCNMatrix4)poseTransform poseTransformAccuracy:(ALPSPoseTransformAccuracy)poseTransformAccuracy;

-(void)alpsLocationManager:(ALPSLocationManager *)locationManager didUpdateLocation:(ALPSLocation*)location poseTransformX:(float)poseTransformX poseTransformY:(float)poseTransformY poseTransformZ:(float)poseTransformZ poseTransformR:(float)poseTransformR poseTransformAccuracy:(ALPSPoseTransformAccuracy)poseTransformAccuracy;
@end


@interface ALPSLocationManager : NSObject

/**
 * Method to obtain a reference to the singleton ALPSLocationManager. This may be called after the ALPSLocationManager has already been initialized with a username and password.
 * @returns Reference to the signelton ALPSLocationManager.
 */
+(id)sharedManager;

/**
 * Method to initialize the signleton ALPSLocationManager obtain a reference to it. The ALPSLocationManager will only be able to localize in areas that exist in the ALPS Web Portal.
 * @param username Your username to the ALPS Web Portal.
 * @param password Your password to the ALPS Web Portal.
 * @param doRecordData Saves all raw ALPS data to disk for debugging if true
 * @param discoveryBSMACs Array of bases station BLE MACs to immediately initialize without running discovery via BLE
 * @returns Reference to the signelton ALPSLocationManager.
 */
+(id)sharedManagerWithUsername:(NSString*)username password:(NSString*)password doRecordData:(BOOL)doRecordData;
+(id)sharedManagerWithUsername:(NSString*)username password:(NSString*)password localServerAddress:(nullable NSString*)localServerAddress doRecordData:(BOOL)doRecordData;
+(id)sharedManagerWithUsername:(NSString*)username password:(NSString*)password localServerAddress:(nullable NSString*)localServerAddress doRecordData:(BOOL)doRecordData discoveryBSMACs:(NSArray*)discoveryBSMACs;

/**
 * Method to start location updates.
 */
-(void)startUpdatingLocation;

/**
 * Method to stop location updates.
 */
-(void)stopUpdatingLocation;

/**
 * Method to supply ARFrames from ARKit to ALPS. This is required for localization.
 * @param frame The ARFrame provided by ARKit 
 */
-(void)updateARFrame:(ARFrame*)frame;

/**
 * Method to supply VIO pose from ARKit to ALPS. This method can be used instead of updateARFrame.
 * @param x x pose coordinate from ARKit
 * @param y y pose coordinate from ARKit
 * @param z z pose coordinate from ARKit
 * @param eulerX eulerX pose angle from ARKit
 * @param eulerY eulerY pose angle from ARKit
 * @param eulerZ eulerZ pose angle from ARKit
 */
-(void)updateARPoseWithX:(float)x y:(float)y z:(float)z eulerX:(float)eulerX eulerY:(float)eulerY eulerZ:(float)eulerZ;

/**
 * Helper method for calculating a location based on  a distance and bearing from a location to a CLLocationCoordinate2D
 * @param bearing from the location in radians.
 * @param distanceMeters from the location in meters.
 * @param origin origin location to calculate the location from.
 * @returns CLLocationCoordinate2D of the calculated location.
 */
- (CLLocationCoordinate2D) locationWithBearing:(double)bearing distance:(double)distanceMeters fromLocation:(CLLocationCoordinate2D)origin;

-(void)updateARTrackingStateWithARCamera:(ARCamera*)camera session:(ARSession*)session;

/**
 * ALPSLocationManagerDelegate object
 */
@property (nonatomic, weak) id<ALPSLocationManagerDelegate> delegate;

/**
 * Boolean representing whether this devices is localizing using ALPS:
 */
@property (nonatomic) BOOL isLocalizing;

@property (nonatomic, readonly) CLAuthorizationStatus authorizationStatus;
@property (nonatomic) CLDeviceOrientation headingOrientation;

@end

NS_ASSUME_NONNULL_END
