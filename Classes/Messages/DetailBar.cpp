//
//  DetailBar.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "DetailBar.hpp"


DetailBar::DetailBar(Creature * creature)
{
    _creature = creature;
    _baseSprite = ScaledSprite::create("Others/CreatureDetail.png");
}


ScaledSprite * DetailBar::getSprite()
{
    return _baseSprite;
}