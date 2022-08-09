//
//  ALPSStoredContour.h
//  alps-framework-objc
//
//  Created by Nick Wilkerson on 11/28/17.
//  Copyright © 2017 Yodel Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Realm/Realm.h>
#import "ALPSStoredContourPoint.h"

RLM_ARRAY_TYPE(ALPSStoredContourPoint)

@interface ALPSStoredContour : RLMObject


@property RLMArray<ALPSStoredContourPoint*><ALPSStoredContourPoint> *points;


@end
