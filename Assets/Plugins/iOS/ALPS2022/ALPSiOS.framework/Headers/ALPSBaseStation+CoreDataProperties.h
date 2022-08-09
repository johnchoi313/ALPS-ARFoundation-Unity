//
//  ALPSBaseStation+CoreDataProperties.h
//  ALPSDemo
//
//  Created by Patrick Lazik on 5/15/22.
//
//

#import "ALPSBaseStation+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface ALPSBaseStation (CoreDataProperties)

+ (NSFetchRequest<ALPSBaseStation *> *)fetchRequest NS_SWIFT_NAME(fetchRequest());

@property (nullable, nonatomic, copy) NSString *bleMAC;
@property (nullable, nonatomic, copy) NSString *ieeeMAC;
@property (nullable, nonatomic, copy) NSDate *lastModified;
@property (nonatomic) float locationX;
@property (nonatomic) float locationY;
@property (nonatomic) float locationZ;
@property (nullable, nonatomic, retain) ALPSFloor *floor;

@end

NS_ASSUME_NONNULL_END
