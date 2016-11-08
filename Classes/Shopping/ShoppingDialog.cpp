//
//  ShoppingDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingDialog.hpp"
#include "ShoppingLayer.hpp"
#include "Constants.hpp"

ShoppingDialog::ShoppingDialog()
{
    _callbackNode = nullptr;
    _returnValue = -1;
}

void ShoppingDialog::showDialog(ShoppingLayer * layer)
{
    _layer = layer;
    _chapterRecord = _layer->getRecord();
    
    _baseSprite = ScaledSprite::create("Others/MessageBox.png");
    _baseSprite->setPosition(Vec2(240, 10));
    _baseSprite->setAnchorPoint(Vec2(0.5f, 0));
    _baseSprite->setScale(Constants::DEFAULT_MESSAGEBOX_SCALE);
    _layer->addChild(_baseSprite);
}

void ShoppingDialog::closeDialog()
{
    _layer->removeChild(_baseSprite);
    _layer->setActiveDialog(nullptr);
    
    if (_callbackNode != nullptr)
    {
        CallbackMethod * method = CallbackMethod::create(_callbackNode, _callbackMethod, _returnValue);
        method->execute();
    }
}

void ShoppingDialog::setCallback(Ref* node, SEL_CALLBACK1 method)
{
    this->_callbackNode = node;
    this->_callbackMethod = method;
}
