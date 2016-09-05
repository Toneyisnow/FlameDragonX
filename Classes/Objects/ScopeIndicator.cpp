//
//  ScopeIndicator.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "ScopeIndicator.hpp"
#include "StringUtil.hpp"
#include "AnimationLibrary.hpp"

ScopeIndicator::ScopeIndicator()
: BattleObject(BattleObject_ScopeIndicator)
{
    initialize("Others/WhiteBlock.png");

    SlideAnimation * animation = AnimationLibrary::getInstance()->getScopeIndicatorAnimation();
    _animator->setAnimation(animation);
}
