//
//  CreatureInfoMessage.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/21/16.
//
//

#include "CreatureInfoMessage.hpp"
#include "MessageLayer.hpp"
#include "LocalizedStrings.hpp"

CreatureInfoMessage::CreatureInfoMessage(Creature * creature)
: CreatureInfoMessage(creature, Vec2(0, 0))
{
}

CreatureInfoMessage::CreatureInfoMessage(Creature * creature, Vec2 clickedAtLocation)
{
    _creature = creature;
    _isBlocking = false;
    
    _position = (clickedAtLocation.x > 240) ? _leftPosition : _rightPosition;
    
}

void CreatureInfoMessage::setPosition(Vec2 position)
{
    _baseSprite->setPosition(position);
}

void CreatureInfoMessage::initDialog()
{
    _baseSprite = ScaledSprite::create("Others/CreatureInfoBarBase.png");
    _baseSprite->setScale(MESSAGEBOX_SCALE);
    _baseSprite->setPosition(_position);
    
    // Name
    std::string name = LocalizedStrings::getInstance()->getCreatureName(_creature->getDefinition()->animationId);
    auto label = Label::createWithTTF(name.c_str(), "fonts/mini_black.ttf", 16);
    label->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(label, Vec2(11, 38));
    
    // Level
    std::string levelStr = StringUtils::format("LV %02d", _creature->creatureData()->level);
    auto levelLabel = Label::createWithTTF(levelStr.c_str(), "fonts/mini_black.ttf", 10);
    _baseSprite->addLabel(levelLabel, Vec2(133, 38));
    
    
    // HP
    _hpBar = Sprite::create(StringUtils::format("Others/CreatureInfoBarHp.png"));
    _hpBar->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addChild(_hpBar, Vec2(28.8, 22.5));
    _hpLabel = nullptr;
    setHp(_creature->creatureData()->hpCurrent);
    
    // MP
    // Fix bug: remove the hpCurrent > 0 condition
    // if (_creature->creatureData()->mpMax > 0 && _creature->creatureData()->mpCurrent > 0)
    if (_creature->creatureData()->mpMax > 0)
    {
        _mpBar = Sprite::create(StringUtils::format("Others/CreatureInfoBarMp.png"));
        _mpBar->setAnchorPoint(Vec2(0, 0.5f));
        _baseSprite->addChild(_mpBar, Vec2(28.8, 10.5));
    }
    _mpLabel = nullptr;
    setMp(_creature->creatureData()->mpCurrent);
    
    if (_messageLayer != nullptr)
    {
        _messageLayer->addChild(_baseSprite);
    }
    else
    {
        _layer->addChild(_baseSprite);
    }
}

void CreatureInfoMessage::removeDialog()
{
    if (_messageLayer != nullptr)
    {
        _messageLayer->removeChild(_baseSprite);
    }
    else
    {
        _layer->removeChild(_baseSprite);
    }
}

void CreatureInfoMessage::setHp(int hpValue)
{
    // HP Bar
    if (hpValue <= 0) {
        _hpBar->setOpacity(0);
    }
    else {
        _hpBar->setOpacity(255);
        float scale = (float)hpValue / _creature->creatureData()->hpMax;
        if (scale < 0.005) {
            scale = 0.005;
        }
        
        _hpBar->setScaleX(scale);
    }
    
    // HP Label
    if (_hpLabel != nullptr) {
        _hpLabel->removeFromParent();
    }
    
    std::string hpStr = (hpValue < 1000) ? StringUtils::format("%03d", hpValue) : "???";
    
    _hpLabel = Label::createWithTTF(hpStr.c_str(), "fonts/mini_black.ttf", 10);
    _hpLabel->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(_hpLabel, Vec2(168, 24));
}

void CreatureInfoMessage::setMp(int mpValue)
{
    if (_creature->creatureData()->mpMax > 0)
    {
        if (mpValue == 0) {
            _mpBar->setOpacity(0);
        } else {
            _mpBar->setOpacity(255);
            _mpBar->setScaleX((float)mpValue / _creature->creatureData()->mpMax);
        }
    }
    
    if (_mpLabel != nullptr) {
        _mpLabel->removeFromParent();
    }
    
    std::string mpStr = (mpValue < 1000) ? StringUtils::format("%03d", mpValue) : "???";
    _mpLabel = Label::createWithTTF(mpStr.c_str(), "fonts/mini_black.ttf", 10);
    _mpLabel->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(_mpLabel, Vec2(168, 11.5));
}

void CreatureInfoMessage::appear()
{
    _baseSprite->setVisible(true);
}

void CreatureInfoMessage::hide()
{
    _baseSprite->setVisible(false);
}

void CreatureInfoMessage::setZOrder(int order)
{
    _baseSprite->setLocalZOrder(order);
}
