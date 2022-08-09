//
//  ALPSOrganization+CoreDataProperties.h
//  
//
//  Created by Patrick Lazik on 8/1/21.
//
//

#import "ALPSOrganization+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface ALPSOrganization (CoreDataProperties)

+ (NSFetchRequest<ALPSOrganization *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSUUID *uuid;
@property (nullable, nonatomic, retain) NSSet<ALPSBuilding *> *buildings;

@end

@interface ALPSOrganization (CoreDataGeneratedAccessors)

- (void)addBuildingsObject:(ALPSBuilding *)value;
- (void)removeBuildingsObject:(ALPSBuilding *)value;
- (void)addBuildings:(NSSet<ALPSBuilding *> *)values;
- (void)removeBuildings:(NSSet<ALPSBuilding *> *)values;

@end

NS_ASSUME_NONNULL_END
