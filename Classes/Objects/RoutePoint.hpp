//
//  RoutePoint.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef RoutePoint_hpp
#define RoutePoint_hpp

#include "cocos2d.h"

USING_NS_CC;

class RoutePoint : public cocos2d::Ref
{
private:
    
    Vector<Vec2> * _points;
    
    
public:
    
    RoutePoint();
    
    void appendPoint(Vec2 point);
    
    
};

#endif /* RoutePoint_hpp */
