//
//  CommonHelper.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#include "CommonHelper.hpp"

bool CommonHelper::IsSamePosition(Vec2 pos1, Vec2 pos2)
{
    return ((int)pos1.x == (int)pos2.x && (int)pos1.y == (int)pos2.y);
}

std::string CommonHelper::IntegerToStringWithMaxValue(int value, int digits)
{
    if (digits == 2) {
        
        if (value < 100) {
            return StringUtils::format("%02d", value);
        } else {
            return "??";
        }
    }
    
    if (digits == 3) {
        
        if (value < 1000) {
            return StringUtils::format("%03d", value);
        } else {
            return "???";
        }
    }
    
    
}
