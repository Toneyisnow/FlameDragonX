//
//  FDNumber.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "FDNumber.hpp"


FDNumber * FDNumber::numberWithInt(int val)
{
    FDNumber * num = new FDNumber(val);
    
    num->autorelease();
    return num;
}

FDNumber::FDNumber(int val)
{
    _value = val;
}

int FDNumber::getValue()
{
    return _value;
}
