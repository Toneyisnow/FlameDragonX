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

CreatureInfoMessage::CreatureInfoMessage(Creature * creature, Vec2 clickedAtLocation)
{
    _creature = creature;
    _isBlocking = false;
    
    _position = (clickedAtLocation.x > 240) ? _leftPosition : _rightPosition;
    
}

void CreatureInfoMessage::initDialog()
{
    _baseSprite = ScaledSprite::create("Others/CreatureInfoBarBase.png");
    _baseSprite->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _baseSprite->setPosition(_position);
    
    // Name
    std::string name = LocalizedStrings::getInstance()->getCreatureName(_creature->getDefinition()->animationId);
    auto label = Label::createWithTTF(name.c_str(), "fonts/mini_black.ttf", 16);
    label->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(label, Vec2(11, 38));
    
    // HP Bar
    Sprite * hpBar = Sprite::create(StringUtils::format("Others/CreatureInfoBarHp.png"));
    hpBar->setAnchorPoint(Vec2(0, 0.5f));
    hpBar->setScaleX(_creature->creatureData()->hpCurrent / _creature->creatureData()->hpMax);
    _baseSprite->addChild(hpBar, Vec2(28.8, 22.5));
    
    // MP Bar
    if (_creature->creatureData()->mpMax > 0 && _creature->creatureData()->mpCurrent > 0)
    {
        Sprite * mpBar = Sprite::create(StringUtils::format("Others/CreatureInfoBarMp.png"));
        mpBar->setAnchorPoint(Vec2(0, 0.5f));
        mpBar->setScaleX(_creature->creatureData()->mpCurrent / _creature->creatureData()->mpMax);
        _baseSprite->addChild(mpBar, Vec2(28.8, 10.5));
    }
    
    // Level
    std::string levelStr = StringUtils::format("LV %02d", _creature->creatureData()->level);
    auto levelLabel = Label::createWithTTF(levelStr.c_str(), "fonts/mini_black.ttf", 10);
    _baseSprite->addLabel(levelLabel, Vec2(133, 38));
    
    // HP value
    std::string hpStr = StringUtils::format("%03d", _creature->creatureData()->hpCurrent);
    auto hpLabel = Label::createWithTTF(hpStr.c_str(), "fonts/mini_black.ttf", 10);
    hpLabel->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(hpLabel, Vec2(168, 24));
    
    // MP value
    std::string mpStr = StringUtils::format("%03d", _creature->creatureData()->mpCurrent);
    auto mpLabel = Label::createWithTTF(mpStr.c_str(), "fonts/mini_black.ttf", 10);
    mpLabel->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(mpLabel, Vec2(168, 11.5));
    
    _messageLayer->addChild(_baseSprite);
}

void CreatureInfoMessage::removeDialog()
{
    _messageLayer->removeChild(_baseSprite);
}