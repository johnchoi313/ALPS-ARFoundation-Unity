//
//  ALPSSolverData.h
//  alps-framework-objc
//
//  Created by Nick Wilkerson on 11/12/17.
//  Copyright © 2017 Yodel Labs. All rights reserved.
//

#import <Realm/Realm.h>

@interface ALPSStoredOrganization : RLMObject
@property NSString *name;
@property NSString *userId;
@property BOOL mine;


@property NSDate *_Nullable createdAt;
@property NSDate *_Nullable updatedAt;

@end
