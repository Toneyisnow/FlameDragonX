//
//  FDRange.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#include "FDRange.hpp"


FDRange * FDRange::rangeWithValues(int min, int max)
{
    FDRange * range = new FDRange();
    
    range->initWithValues(min, max);
    range->autorelease();
    return range;
}

void FDRange::initWithValues(int min, int max)
{
    _minValue  = min;
    _maxValue = max;
}

bool FDRange::containsValue(int val)
{
    return (val >= _minValue && val <= _maxValue);
}


int FDRange::getMin()
{
    return _minValue;
}

int FDRange::getMax()
{
    return _maxValue;
}