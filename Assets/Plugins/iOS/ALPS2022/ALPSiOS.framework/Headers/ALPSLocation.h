/******************************************************************************
 *  ALPS, The Acoustic Local Positioning System.
 *  ALPSLocation
 *  Yodel Labs, 2021
 *
 *  Contributing Author(s):
 *  Patrick Lazik
 *
 *******************************************************************************/

/**
 *  Location class for storing location, heading, accuracy, floor and associated timestamp in the ALPS reference frame.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ALPSFloor;

@interface ALPSLocation : NSObject

@property (nonatomic) float x; /**< x coordinate in meters in the ALPS reference frame */
@property (nonatomic) float y; /**< y coordinate in meters in the ALPS reference frame */
@property (nonatomic) float z; /**< z coordinate in meters from the floor in the ALPS reference frame */
@property (nonatomic) float heading; /**< heading in radians in the ALPS reference frame */
@property (nonatomic) float accuracyX; /**< Standard deviation of the uncertainty of this location estimate along the x axis in meters */
@property (nonatomic) float accuracyY; /**<  Standard deviation of the uncertainty of this location estimate along the y axis in meters */
@property (nonatomic) float accuracyZ; /**< Standard deviation of the uncertainty of this location estimate along the z axis in meters */
@property (nonatomic) float accuracyHeading; /**< Standard deviation of the uncertainty of this heading estimate radians */
@property (nonatomic) ALPSFloor* floor; /**< The floor corresponding to this location */
@property (nonatomic) double timeStamp; /**< Time when this location was estimated. Expressed in seconds since boot time of the device (monotonic clock). */

/**
 * Empty constructor for ALPSLocation.
 * @returns Reference to a new ALPSLocation object.
 */
-(id) init;

/**
 * Empty constructor for ALPSLocation.
 * @param x x coordinate in meters in the ALPS reference frame.
 * @param y y coordinate in meters in the ALPS reference frame.
 * @param z z coordinate in meters in the ALPS reference frame.
 * @param heading heading in radians in the ALPS reference frame.
 * @param accuracyX Standard deviation of the uncertainty of this location estimate along the x axis in meters.
 * @param accuracyY Standard deviation of the uncertainty of this location estimate along the y axis in meters.
 * @param accuracyZ Standard deviation of the uncertainty of this location estimate along the z axis in meters.
 * @param accuracyHeading Standard deviation of the uncertainty of this heading estimate radians.
 * @param floor The floor corresponding to this location.
 * @param timeStamp Time when this location was estimated. Expressed in seconds since boot time of the device (monotonic clock).
 * @returns Reference to a new ALPSLocation object with the specified parameters.
 */
-(id) initWithX:(float)x y:(float)y z:(float)z heading:(float)heading accuracyX:(float)accuracyX accuracyY:(float)accuracyY accuracyZ:(float)accuracyZ accuracyHeading:(float)accuracyHeading floor:(ALPSFloor*)floor timeStamp:(double)timeStamp;

@end

NS_ASSUME_NONNULL_END
