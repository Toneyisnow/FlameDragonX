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
#include "FDPoint.hpp"

USING_NS_CC;

class RoutePoint : public cocos2d::Ref
{
private:
    
    Vector<FDPoint *> * _points;
    
    
public:
    
    RoutePoint();
    ~RoutePoint();
    
    void appendPoint(Vec2 point);
    void insertPoint(Vec2 point);
    
    int getCount();
    int getLength();
    
    Vec2 pointAt(int index);
};

#endif /* RoutePoint_hpp */
