//
//  RoutePoint.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "RoutePoint.hpp"


RoutePoint::RoutePoint()
{
    _points = new Vector<FDPoint *>();
}

RoutePoint::~RoutePoint()
{
    _points->clear();
    delete _points;
}

void RoutePoint::appendPoint(Vec2 point)
{
    _points->pushBack(FDPoint::create(point));
}

void RoutePoint::insertPoint(Vec2 point)
{
    _points->insert(0, FDPoint::create(point));
}

int RoutePoint::getCount()
{
    return (int)_points->size();
}

int RoutePoint::getLength()
{
    if (_points->size() == 0) {
        return 0;
    }
    
    int totalLength = 0;
    for (int i = 0; i < _points->size() - 1; i ++) {
        Vec2 pos1 = _points->at(i)->getValue();
        Vec2 pos2 = _points->at(i+1)->getValue();
        
        totalLength += std::abs(pos1.x - pos2.x) + std::abs(pos1.y - pos2.y);
    }
    
    return totalLength;
}

Vec2 RoutePoint::pointAt(int index)
{
    return _points->at(index)->getValue();
}
