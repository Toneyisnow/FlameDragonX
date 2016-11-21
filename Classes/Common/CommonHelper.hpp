//
//  CommonHelper.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#ifndef CommonHelper_hpp
#define CommonHelper_hpp

#include "cocos2d.h"

USING_NS_CC;

class CommonHelper : public cocos2d::Ref
{
public:
    
    static bool IsSamePosition(Vec2 pos1, Vec2 pos2);
    
    static std::string IntegerToStringWithMaxValue(int value, int digits);
    
};

#endif /* CommonHelper_hpp */
