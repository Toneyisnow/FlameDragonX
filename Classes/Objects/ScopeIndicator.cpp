//
//  ScopeIndicator.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "ScopeIndicator.hpp"
#include "StringUtil.hpp"

ScopeIndicator::ScopeIndicator()
: BattleObject(BattleObject_ScopeIndicator)
{
    _animation = nullptr;
    _baseSprite = Sprite::create("Others/WhiteBlock.png");

}
