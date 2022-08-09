//
//  ALPSBeacon+CoreDataProperties.h
//  
//
//  Created by Patrick Lazik on 8/1/21.
//
//

#import "ALPSBeacon+CoreDataClass.h"


NS_ASSUME_NONNULL_BEGIN

@interface ALPSBeacon (CoreDataProperties)

+ (NSFetchRequest<ALPSBeacon *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSString *bleMAC;
@property (nullable, nonatomic, copy) NSString *ieeeMAC;
@property (nullable, nonatomic, copy) NSDate *lastModified;
@property (nonatomic) float locationX;
@property (nonatomic) float locationY;
@property (nonatomic) float locationZ;
@property (nullable, nonatomic, retain) NSArray *rangingChirps;
@property (nullable, nonatomic, retain) NSArray *rangingChirpSchedule;
@property (nonatomic) int16_t rangingNumSlots;
@property (nonatomic) int16_t rangingSlotLength;
@property (nullable, nonatomic, retain) ALPSFloor *floor;

@end

NS_ASSUME_NONNULL_END
