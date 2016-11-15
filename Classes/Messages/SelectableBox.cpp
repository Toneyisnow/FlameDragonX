//
//  SelectableBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "SelectableBox.hpp"

SelectableBox::SelectableBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method)
{
    _creature = creature;
    _operatingType = type;
    
    _baseSprite = ScaledSprite::create("Others/ContainerBase.png");

    _initialX = 5;
    _initialY = 5;
    _spacingX = 100;
    _spacingY = 25;
    
}

ScaledSprite * SelectableBox::getSprite()
{
    return _baseSprite;
}

int SelectableBox::handleClick(Vec2 location)
{
    log("Clicked at SelectableBox (%f, %f)", location.x, location.y);
    
    return 0;
}
