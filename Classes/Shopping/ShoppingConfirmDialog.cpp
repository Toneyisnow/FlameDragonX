//
//  ShoppingConfirmDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingConfirmDialog.hpp"
#include "ShoppingLayer.hpp"

ShoppingConfirmDialog::ShoppingConfirmDialog(std::string message)
{
    _message = message;
}

void ShoppingConfirmDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingDialog::showDialog(layer);
    
    // Add message
    
    
    // Add Yes and No Buttons
    TouchableSprite * yesButton = TouchableSprite::create("Others/ConfirmButtonYes.png");
    yesButton->setCallback(this, CALLBACK0_SELECTOR(ShoppingConfirmDialog::onClickedYes));
    _baseSprite->addChild(yesButton, Vec2(220, 20));
    
    TouchableSprite * noButton = TouchableSprite::create("Others/ConfirmButtonNo.png");
    noButton->setCallback(this, CALLBACK0_SELECTOR(ShoppingConfirmDialog::onClickedNo));
    _baseSprite->addChild(noButton, Vec2(270, 20));
    
    
    
}

void ShoppingConfirmDialog::onClickedYes()
{
    _returnValue = 1;
    this->closeDialog();
}

void ShoppingConfirmDialog::onClickedNo()
{
    _returnValue = -1;
    this->closeDialog();
}
