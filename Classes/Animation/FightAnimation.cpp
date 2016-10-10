//
//  FightAnimation.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#include "FightAnimation.hpp"

FightAnimation::FightAnimation(FightAnimationDefinition * def)
: SlideAnimation(DEFAULT_INTERVAL, false, false)
{
    _definition = def;
}
