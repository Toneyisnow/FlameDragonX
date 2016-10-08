//
//  RangeScopeResolver.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "RangeScopeResolver.hpp"
#include "BattleField.hpp"

RangeScopeResolver::RangeScopeResolver(BattleField * field, Vec2 point, FDRange * range)
{
    this->_field = field;
    this->_point = point;
    this->_range = range;
}

Vector<FDPoint *> RangeScopeResolver::calculcate()
{
    Vector<FDPoint *> result;
    
    if (_range == nullptr)
    {
        return result;
    }
        
    for (int r = _range->getMin(); r <= _range->getMax(); r++) {
        
        for (int k = 0; k <= r; k ++) {
            
            appendPoint(result, _point.x + r - k, _point.y + k);
            
            if ( k > 0)
                appendPoint(result, _point.x + r - k, _point.y - k);
            
            if ( k < r)
                appendPoint(result, _point.x - r + k, _point.y + k);
            
            if ( k > 0 && k < r)
                appendPoint(result, _point.x - r + k, _point.y - k);
        }
    }
    
    return result;
}

void RangeScopeResolver::appendPoint(Vector<FDPoint *> &list, int x, int y)
{
    if (x > 0 && x <= _field->getFieldSize().width && y > 0 && y <= _field->getFieldSize().height) {
        list.pushBack(FDPoint::create(x, y));
    }
}
