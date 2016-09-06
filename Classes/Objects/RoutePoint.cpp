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

Vec2 RoutePoint::pointAt(int index)
{
    return _points->at(index)->getValue();
}