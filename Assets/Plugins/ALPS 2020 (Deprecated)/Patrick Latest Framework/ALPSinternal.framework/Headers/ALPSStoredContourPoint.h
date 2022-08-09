//
//  ALPSStoredContourPoint.h
//  alps-framework-objc
//
//  Created by Nick Wilkerson on 11/28/17.
//  Copyright © 2017 Yodel Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Realm/Realm.h>

@interface ALPSStoredContourPoint : RLMObject

@property NSNumber<RLMDouble> *x;
@property NSNumber<RLMDouble> *y;

@end
