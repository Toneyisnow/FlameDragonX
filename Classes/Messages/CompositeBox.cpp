//
//  MessageBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "CompositeBox.hpp"
#include "MessageLayer.hpp"
#include "ItemBox.hpp"
#include "MagicBox.hpp"

CompositeBox::CompositeBox(Creature * creature, MessageBoxType type, MessageBoxOperatingType oType)
{
    this->_creature = creature;
    this->_type = type;
    this->_operatingType = oType;
}

CompositeBox::~CompositeBox()
{
    
}

void CompositeBox::initDialog()
{
    _datoBar = new DatoBar(_creature->getDefinition()->animationId);
    _datoBar->getSprite()->setAnchorPoint(Vec2(1.0f, 0));
    _datoBar->getSprite()->setPosition(Vec2(160, 162));
    _datoBar->getSprite()->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _messageLayer->addChild(_datoBar->getSprite());
    
    _detailBar = new DetailBar(_creature);
    _detailBar->getSprite()->setAnchorPoint(Vec2(0, 0));
    _detailBar->getSprite()->setPosition(Vec2(162, 162));
    _detailBar->getSprite()->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _messageLayer->addChild(_detailBar->getSprite());
    
    if (_type == MessageBoxType_Item) {
        _mainBox = new ItemBox(_creature, _operatingType);
    }
    else
    {
        _mainBox = new MagicBox(_creature, _operatingType);
    }
    
    _mainBox->getSprite()->setAnchorPoint(Vec2(0.5f, 1.0f));
    _mainBox->getSprite()->setPosition(Vec2(240, 158));
    _mainBox->getSprite()->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _messageLayer->addChild(_mainBox->getSprite());
}

void CompositeBox::removeDialog()
{
    _messageLayer->removeChild(_datoBar->getSprite());
    _messageLayer->removeChild(_detailBar->getSprite());
    _messageLayer->removeChild(_mainBox->getSprite());
    
    _datoBar->release();
    _detailBar->release();
    _mainBox->release();
}

FDActivity * CompositeBox::onEnterActivity()
{
    return nullptr;
}

FDActivity * CompositeBox::onExitActivity()
{
    return nullptr;
}

void CompositeBox::handleClick(Vec2 location)
{
    
}