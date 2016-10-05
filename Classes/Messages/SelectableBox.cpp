//
//  SelectableBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "SelectableBox.hpp"

SelectableBox::SelectableBox()
{
    _baseSprite = ScaledSprite::create("Others/ContainerBase.png");

    _initialX = 5;
    _initialY = 5;
    _spacingX = 100;
    _spacingY = 25;
    _objectCount = 12;
    
    for (int i = 0; i < _objectCount; i++) {
        drawObject(i);
    }
}

ScaledSprite * SelectableBox::getSprite()
{
    return _baseSprite;
}

void SelectableBox::drawObject(int index)
{
    std::string lable1 = "First Item";
    auto label = Label::createWithTTF(lable1.c_str(), "fonts/mini_black.ttf", 14);
    label->setColor(Color3B(255, 255, 255));
    label->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(label, Vec2(_initialX + (index / 4) * _spacingX, 100 - _initialY - (index % 4) * _spacingY));
}

int SelectableBox::handleClick(Vec2 location)
{
    log("Clicked at SelectableBox (%f, %f)", location.x, location.y);
    
    return 0;
}
