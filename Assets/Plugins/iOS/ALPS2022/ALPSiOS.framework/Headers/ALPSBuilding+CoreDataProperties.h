//
//  ALPSBuilding+CoreDataProperties.h
//  
//
//  Created by Patrick Lazik on 8/1/21.
//
//

#import "ALPSBuilding+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface ALPSBuilding (CoreDataProperties)

+ (NSFetchRequest<ALPSBuilding *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSString *address;
@property (nullable, nonatomic, copy) NSDate *childLastModified;
@property (nullable, nonatomic, copy) NSDate *lastModified;
@property (nullable, nonatomic, copy) NSString *name;
@property (nullable, nonatomic, copy) NSURL *serverURL;
@property (nullable, nonatomic, copy) NSUUID *uuid;
@property (nullable, nonatomic, retain) NSSet<ALPSFloor *> *floors;
@property (nullable, nonatomic, retain) ALPSOrganization *organization;

@end

@interface ALPSBuilding (CoreDataGeneratedAccessors)

- (void)addFloorsObject:(ALPSFloor *)value;
- (void)removeFloorsObject:(ALPSFloor *)value;
- (void)addFloors:(NSSet<ALPSFloor *> *)values;
- (void)removeFloors:(NSSet<ALPSFloor *> *)values;

@end

NS_ASSUME_NONNULL_END
