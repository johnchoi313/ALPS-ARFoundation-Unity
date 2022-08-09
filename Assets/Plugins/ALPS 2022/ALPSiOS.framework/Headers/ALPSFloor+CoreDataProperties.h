//
//  ALPSFloor+CoreDataProperties.h
//  ALPSDemo
//
//  Created by Patrick Lazik on 5/15/22.
//
//

#import "ALPSFloor+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface ALPSFloor (CoreDataProperties)

+ (NSFetchRequest<ALPSFloor *> *)fetchRequest NS_SWIFT_NAME(fetchRequest());

@property (nonatomic) float bleDiscoveryRadius;
@property (nullable, nonatomic, copy) NSDate *childLastModified;
@property (nullable, nonatomic, copy) NSURL *floorPlan;
@property (nullable, nonatomic, copy) NSURL *floorPlanGrid;
@property (nullable, nonatomic, copy) NSDate *floorPlanGridLastModified;
@property (nullable, nonatomic, copy) NSDate *floorPlanLastModified;
@property (nonatomic) float floorPlanPixelsPerMeter;
@property (nullable, nonatomic, copy) NSURL *floorPlanVectorFonts;
@property (nullable, nonatomic, copy) NSURL *floorPlanVectorHigh;
@property (nullable, nonatomic, copy) NSDate *floorPlanVectorLastModified;
@property (nullable, nonatomic, copy) NSURL *floorPlanVectorLow;
@property (nullable, nonatomic, copy) NSURL *floorPlanVectorSprites;
@property (nullable, nonatomic, copy) NSURL *floorPlanVectorStyle;
@property (nullable, nonatomic, copy) NSString *floorPlanVectorStyleTemplate;
@property (nullable, nonatomic, copy) NSDate *lastModified;
@property (nullable, nonatomic, copy) NSString *name;
@property (nonatomic) int16_t number;
@property (nonatomic) double additionalTimesyncOffset;
@property (nullable, nonatomic, copy) NSUUID *uuid;
@property (nullable, nonatomic, retain) NSSet<ALPSBaseStation *> *basestations;
@property (nullable, nonatomic, retain) NSSet<ALPSBeacon *> *beacons;
@property (nullable, nonatomic, retain) ALPSBuilding *building;

@end

@interface ALPSFloor (CoreDataGeneratedAccessors)

- (void)addBasestationsObject:(ALPSBaseStation *)value;
- (void)removeBasestationsObject:(ALPSBaseStation *)value;
- (void)addBasestations:(NSSet<ALPSBaseStation *> *)values;
- (void)removeBasestations:(NSSet<ALPSBaseStation *> *)values;

- (void)addBeaconsObject:(ALPSBeacon *)value;
- (void)removeBeaconsObject:(ALPSBeacon *)value;
- (void)addBeacons:(NSSet<ALPSBeacon *> *)values;
- (void)removeBeacons:(NSSet<ALPSBeacon *> *)values;

@end

NS_ASSUME_NONNULL_END
