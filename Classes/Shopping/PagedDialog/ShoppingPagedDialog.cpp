//
//  ShoppingPagedDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingPagedDialog.hpp"
#include "TouchableSprite.hpp"
#include "Constants.hpp"

ShoppingPagedDialog::ShoppingPagedDialog(int index)
{
    _pageIndex = index;
}

void ShoppingPagedDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingDialog::showDialog(layer);
    
    // Add the two buttons here
    
    if (_pageIndex > 0)
    {
        // Show the UP button
        TouchableSprite * upButton = TouchableSprite::create("Others/Arrow_up.png");
        upButton->setScale(Constants::DEFAULT_MESSAGEBOX_SCALE);
        upButton->setCallback(this, CALLBACK0_SELECTOR(ShoppingPagedDialog::clickedUp));
        _baseSprite->addChild(upButton, Vec2(283, 10));
    }
    
    if (this->getTotalCount() > (_pageIndex + 1) * getMaxPerPage())
    {
        // Show the DOWN button
        TouchableSprite * downButton = TouchableSprite::create("Others/Arrow_down.png");
        downButton->setScale(Constants::DEFAULT_MESSAGEBOX_SCALE);
        downButton->setCallback(this, CALLBACK0_SELECTOR(ShoppingPagedDialog::clickedDown));
        _baseSprite->addChild(downButton, Vec2(283, 10));
    }
    
    
}

int ShoppingPagedDialog::getMaxPerPage()
{
    return 1;
}

int ShoppingPagedDialog::getTotalCount()
{
    return 1;
}


void ShoppingPagedDialog::clickedDown()
{
    
}

void ShoppingPagedDialog::clickedUp()
{
    
}
