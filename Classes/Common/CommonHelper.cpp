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
