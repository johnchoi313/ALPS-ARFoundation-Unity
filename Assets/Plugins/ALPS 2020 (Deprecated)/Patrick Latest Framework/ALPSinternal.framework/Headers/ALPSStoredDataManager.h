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
#import <UIKit/UIKit.h>
#import "ALPSStoredGrid.h"
#import "ALPSStoredBeacon.h"
#import "ALPSStoredOrganization.h"

extern NSString * _Nonnull const ALPSStoredDataErrorDomain;

@interface ALPSStoredDataManager : NSObject

+(ALPSStoredDataManager * _Nonnull)sharedInstance;

-(void)registerWithUsername:(NSString *_Nonnull)username password:(NSString *_Nonnull)password completion:(void(^_Nullable)(BOOL success, NSError *_Nullable error))completion;

-(void)logInWithUsername:(NSString *_Nonnull)username password:(NSString *_Nonnull)password completion:(void(^_Nullable)(BOOL success, NSError *_Nullable error))completion;

-(void)userOrganizationsWithCallback:(void(^_Nullable)(NSArray *_Nullable, NSError *_Nullable))callback;

-(void)subscribeToNotificationsForOrganizationsForAnyEventWithBlock:(void(^)(void))callback;

-(void)subscribeToDownloadProgressNotificationForOrganizationsWithProgressBlock:(void(^)(double progress))progressBlock callback:(void(^)(NSError *error))callback;

-(void)connectUsingPartialSyncToGlobalOrganizationWithPath:(NSString *)orgName callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)connectUsingPartialSyncToUserOrganizationWithName:(NSString *)orgName callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)connectToUserOrganizationWithName:(NSString *_Nonnull)orgName  callback:(void(^_Nullable)(BOOL success, NSError * _Nullable error))callback;

-(void)connectToGlobalOrganizationWithPath:(NSString *_Nonnull)orgName  callback:(void(^_Nullable)(BOOL success, NSError * _Nullable error))callback;

-(void)connectToUserRemoteRealmIdentifiedBy:(NSString *_Nonnull)remoteRealmIdentifier partialSync:(BOOL)partialSync callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)connectToGlobalRemoteRealmIdentifiedBy:(NSString *_Nonnull)remoteRealmIdentifier partialSync:(BOOL)partialSync callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;


-(void)createUserOrganizationWithName:(NSString *_Nonnull)orgName callback:(void(^_Nullable)(ALPSStoredOrganization *_Nullable org, NSError *_Nullable))callback;

-(void)createGlobalOrganizationWithPath:(NSString *_Nonnull)orgPath callback:(void(^_Nullable)(ALPSStoredOrganization *_Nullable org, NSError *_Nullable))callback;

-(void)connectWithReadOnlyAccessToGlobalRemoteRealmIdentifiedBy:(NSString *_Nonnull)remoteRealmIdentifier callback:(void(^_Nonnull)(BOOL success, NSError *_Nullable error))callback;


-(void)connectAndFindBeacons;

#pragma mark - grids

-(void)createRemoteGridWithIdentifier:(NSString *_Nonnull)identifier
                             latitude:(NSNumber *_Nonnull)latitude
                            longitude:(NSNumber *_Nullable)longitude
                                floor:(NSNumber *_Nullable)floor
                             rotation:(NSNumber *_Nullable)rotation
                             gridData:(NSData *_Nullable)gridData
                            gridWidth:(NSNumber *_Nullable)gridWidth
                            gridScale:(NSNumber *_Nullable)gridScale
                       floorPlanImage:(UIImage *_Nullable)floorPlanImage
                       floorPlanScale:(NSNumber *_Nullable)floorPlanScale
                             contours:(NSArray<NSArray<NSValue*>*>*_Nullable)contours
                            tdmaSlots:(NSNumber *)tdmaSlots
                       tdmaSlotLength:(NSNumber *)tdmaSlotLength
                     slotRecordLength:(NSNumber *)slotRecordLendth
                             callback:(void(^_Nullable)(ALPSStoredGrid *_Nullable grid, NSError * _Nullable error))callback;

-(void)createLocalGridWithIdentifier:(NSString *_Nonnull)identifier
                            latitude:(NSNumber *_Nonnull)latitude
                           longitude:(NSNumber *_Nullable)longitude
                               floor:(NSNumber *_Nullable)floor
                            rotation:(NSNumber *_Nullable)rotation
                            gridData:(NSData *_Nullable)gridData
                           gridWidth:(NSNumber *_Nullable)gridWidth
                           gridScale:(NSNumber *_Nullable)gridScale
                      floorPlanImage:(UIImage *_Nullable)floorPlanImage
                      floorPlanScale:(NSNumber *_Nullable)floorPlanScale
                            contours:(NSArray<NSArray<NSValue*>*>*_Nullable)contours
                           tdmaSlots:(NSNumber *)tdmaSlots
                      tdmaSlotLength:(NSNumber *)tdmaSlotLength
                    slotRecordLength:(NSNumber *)slotRecordLendth
                            callback:(void(^_Nullable)(ALPSStoredGrid *_Nullable grid, NSError * _Nullable error))callback;

-(void)createGridInRealm:(RLMRealm *_Nonnull)realm
          withIdentifier:(NSString *_Nonnull)identifier
                latitude:(NSNumber *_Nullable)latitude
               longitude:(NSNumber *_Nullable)longitude
                   floor:(NSNumber *_Nullable)floor
                rotation:(NSNumber *_Nullable)rotation
                gridData:(NSData *_Nullable)gridData
               gridWidth:(NSNumber *_Nullable)gridWidth
               gridScale:(NSNumber *_Nullable)gridScale
          floorPlanImage:(UIImage *_Nullable)floorPlanImage
          floorPlanScale:(NSNumber *_Nullable)floorPlanScale
                contours:(NSArray<NSArray<NSValue*>*>*_Nullable)contours
               tdmaSlots:(NSNumber *)tdmaSlots
          tdmaSlotLength:(NSNumber *)tdmaSlotLength
        slotRecordLength:(NSNumber *)slotRecordLendth
                callback:(void(^_Nullable)(ALPSStoredGrid *_Nullable grid, NSError * _Nullable error))callback;

-(ALPSStoredGrid *_Nullable)findLocalGridWithIdentifier:(NSString *_Nonnull)identifier;

-(ALPSStoredGrid *_Nullable)findRemoteGridWithIdentifier:(NSString *_Nonnull)identifier;

-(NSArray *_Nonnull)findAllRemoteGrids;

-(void)deleteRemoteGrid:(ALPSStoredGrid *_Nonnull)grid callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;
-(void)deleteLocalGrid:(ALPSStoredGrid *_Nonnull)grid callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;
-(void)deleteGrid:(ALPSStoredGrid *_Nonnull)grid inRealm:(RLMRealm *_Nonnull)realm callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

/*
 *  If you don't want to update a property, leave it as nil
 *
 */
-(void)updateRemoteGrid:(ALPSStoredGrid *_Nonnull)grid
           withLatitude:(NSNumber *_Nullable)latitude
              longitude:(NSNumber *_Nullable)longitude
                  floor:(NSNumber *_Nullable)floor
               rotation:(NSNumber *_Nullable)rotation
               gridData:(NSData *_Nullable)gridData
              gridWidth:(NSNumber *_Nullable)gridWidth
              gridScale:(NSNumber *_Nullable)gridScale
         floorPlanImage:(UIImage *_Nullable)floorPlanImage
         floorPlanScale:(NSNumber *_Nullable)floorPlanScale
               contours:(NSArray<NSArray<NSValue*>*>*_Nullable)contours
              tdmaSlots:(NSNumber *_Nullable)tdmaSlots
         tdmaSlotLength:(NSNumber *_Nullable)tdmaSlotLength
       slotRecordLength:(NSNumber *_Nullable)slotRecordLendth
               callback:(void(^_Nullable)(BOOL success, NSError *error))callback;

/*
 *  create beacon in grid
 */


-(void)createLocalBeaconAsPartOfGridIdentifiedBy:(NSString *_Nonnull)gridIdentifier
                                      withBleMac:(NSString *_Nonnull)bleMac
                                  fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                               x:(NSNumber *_Nonnull)x
                                               y:(NSNumber *_Nonnull)y
                                               z:(NSNumber *_Nonnull)z
                                      slotNumber:(NSNumber *_Nonnull)slotNumber
                                        callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;

-(void)createLocalBeaconAsPartOfGrid:(ALPSStoredGrid *_Nonnull)grid
                          withBleMac:(NSString *_Nonnull)bleMac
                      fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                   x:(NSNumber *_Nonnull)x
                                   y:(NSNumber *_Nonnull)y
                                   z:(NSNumber *_Nonnull)z
                          slotNumber:(NSNumber *_Nonnull)slotNumber
                            callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;

-(void)createRemoteBeaconAsPartOfGridIdentifiedBy:(NSString *_Nonnull)gridIdentifier
                                       withBleMac:(NSString *_Nonnull)bleMac
                                   fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                                x:(NSNumber *_Nonnull)x
                                                y:(NSNumber *_Nonnull)y
                                                z:(NSNumber *_Nonnull)z
                                       slotNumber:(NSNumber *_Nonnull)slotNumber
                                         callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;

-(void)createRemoteBeaconAsPartOfGrid:(ALPSStoredGrid *_Nonnull)grid
                           withBleMac:(NSString *_Nonnull)bleMac
                       fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                    x:(NSNumber *_Nonnull)x
                                    y:(NSNumber *_Nonnull)y
                                    z:(NSNumber *_Nonnull)z
                           slotNumber:(NSNumber *_Nonnull)slotNumber
                             callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;

-(void)createBeaconInRealm:(RLMRealm *_Nonnull)realm
  asPartOfGridIdentifiedBy:(NSString *_Nonnull)gridIdentifier
                withBleMac:(NSString *_Nonnull)bleMac
            fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                         x:(NSNumber *_Nonnull)x
                         y:(NSNumber *_Nonnull)y
                         z:(NSNumber *_Nonnull)z
                slotNumber:(NSNumber *_Nonnull)slotNumber
                  callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;

-(void)createBeaconInRealm:(RLMRealm *_Nonnull)realm
              asPartOfGrid:(ALPSStoredGrid *_Nonnull)gridIdentifier
                withBleMac:(NSString *_Nonnull)bleMac
            fifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                         x:(NSNumber *_Nonnull)x
                         y:(NSNumber *_Nonnull)y
                         z:(NSNumber *_Nonnull)z
                slotNumber:(NSNumber *_Nonnull)slotNumber
                  callback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, NSError * _Nullable error))callback;



/*
 *  update beacon
 */

-(void)updateRemoteBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac
                         withFifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                          x:(NSNumber *_Nonnull)x
                                          y:(NSNumber *_Nonnull)y
                                          z:(NSNumber *_Nonnull)z
                                 slotNumber:(NSNumber *_Nonnull)slotNumber;

-(void)updateLocalBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac
                        withFifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                                         x:(NSNumber *_Nonnull)x
                                         y:(NSNumber *_Nonnull)y
                                         z:(NSNumber *_Nonnull)z
                                slotNumber:(NSNumber *_Nonnull)slotNumber;

-(void)updateBeaconInRealm:(RLMRealm *_Nonnull)realm
        identifiedByBleMac:(NSString *_Nonnull)bleMac
        withFifteenFourMac:(NSString *_Nonnull)fifteenFourMac
                         x:(NSNumber *_Nonnull)x
                         y:(NSNumber *_Nonnull)y
                         z:(NSNumber *_Nonnull)z
                slotNumber:(NSNumber *_Nonnull)slotNumber;


-(void)deleteRemoteBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;
-(void)deleteLocalBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)deleteBeaconInRealm:(RLMRealm *_Nonnull)realm identifiedByBleMac:(NSString *_Nonnull)bleMac callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)deleteRemoteBeacon:(ALPSStoredBeacon *_Nonnull)beacon callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;
-(void)deleteLocalBeacon:(ALPSStoredBeacon *_Nonnull)beacon callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;

-(void)deleteBeacon:(ALPSStoredBeacon *_Nonnull)beacon inRealm:(RLMRealm *_Nonnull)realm callback:(void(^_Nullable)(BOOL success, NSError *_Nullable error))callback;





-(ALPSStoredBeacon *)findLocalBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac;

-(ALPSStoredBeacon *)findRemoteBeaconIdentifiedByBleMac:(NSString *_Nonnull)bleMac;

-(NSArray *_Nonnull)findAllRemoteBeacons;

-(void)findBeaconAndGridForBeaconBleMac:(NSString *_Nonnull)beaconBleMac inRemoteRealmIdentifiedBy:(NSString *_Nonnull)remoteRealmIdentifier withCallback:(void(^_Nullable)(ALPSStoredBeacon *_Nullable beacon, ALPSStoredGrid *_Nullable grid, NSError *_Nullable error))callback;


-(void)printMyPrivileges;

/**
 *
 *  @p realmIdentifier should be in the full path format /userid/realmid
 *
 */
-(void)shareRealmIdentifiedBy:(NSString *)realmIdentifier callback:(void(^)(NSString *token, NSError *error))callback;


@property (nonatomic, readonly) BOOL isLoggedIn;


@property (nonatomic) RLMRealm *connectedRemoteRealm;

@property (nonatomic, readonly) NSString *currentUserId;
@property (nonatomic, readonly) NSString *currentRealmPath;


@end

