//
//  FDPoint.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#include "FDPoint.hpp"

FDPoint * FDPoint::create(int x, int y)
{
    FDPoint * p = new FDPoint(Vec2(x, y));
    
    p->autorelease();
    return p;
}

FDPoint * FDPoint::create(Vec2 point)
{
    FDPoint * p = new FDPoint(point);
    
    p->autorelease();
    return p;
}

FDPoint::FDPoint(Vec2 point)
{
    _data = point;
}

Vec2 FDPoint::getValue()
{
    return _data;
}
