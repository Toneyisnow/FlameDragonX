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
            
            result.pushBack(FDPoint::create(_point.x + r - k, _point.y + k));
            
            if ( k > 0)
                result.pushBack(FDPoint::create(_point.x + r - k, _point.y - k));
            
            if ( k < r)
                result.pushBack(FDPoint::create(_point.x - r + k, _point.y + k));
            
            if ( k > 0 && k < r)
                result.pushBack(FDPoint::create(_point.x - r + k, _point.y - k));
        }
    }
    
    return result;
}
