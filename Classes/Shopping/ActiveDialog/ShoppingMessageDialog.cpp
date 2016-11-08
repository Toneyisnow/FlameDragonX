//
//  ShoppingMessageDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingMessageDialog.hpp"

#include "ShoppingLayer.hpp"

ShoppingMessageDialog::ShoppingMessageDialog(std::string message)
{
    _message = message;
}

void ShoppingMessageDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingActiveDialog::showDialog(layer);
    
    // Add message
    Label * message = Label::createWithTTF(_message.c_str(), "fonts/mini_black.ttf", DEFAULT_FONT_SIZE);
    message->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(message, MESSAGE_POSITION);
    
    
}
