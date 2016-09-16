//
//  SpeakMessage.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "SpeakMessage.hpp"
#include "MessageLayer.hpp"

SpeakMessage::SpeakMessage(std::string content)
{
    _creature = nullptr;
    _content = content;
}

SpeakMessage::SpeakMessage(Creature * creature, std::string content)
{
    _creature = creature;
    _content = content;
}

void SpeakMessage::initDialog()
{
    _messageBox = Sprite::create("Others/MessageBox.png");
    _messageBox->setPosition(Vec2(240, 160));
    _messageBox->setAnchorPoint(Vec2(0.5f, 0));
    _messageBox->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _messageLayer->addChild(_messageBox);
    
    int creatureDatoId = (_creature != nullptr ? _creature->getDefinition()->animationId : 0);
    Sprite * dato = Sprite::create(StringUtils::format("Dato/Dato-%03d-1.png", creatureDatoId));
    dato->setAnchorPoint(Vec2(0, 0));
    dato->setPosition(Vec2(1, 1));
    _messageBox->addChild(dato, 1);
    
    auto label = Label::createWithTTF(_content.c_str(), "fonts/mini_black.ttf", 8);
    
    label->setColor(Color3B(255, 255, 255));
    label->setPosition(Vec2(30, 20));
    label->setAnchorPoint(Vec2(0, 0.5f));
    _messageBox->addChild(label, 1);
    
    
    
}
void SpeakMessage::removeDialog()
{
    _messageLayer->removeChild(_messageBox);
}

FDActivity * SpeakMessage::onEnterActivity()
{
    return nullptr;
}

FDActivity * SpeakMessage::onExitActivity()
{
    return nullptr;
}

void SpeakMessage::handleClick(Vec2 location)
{
    _returnValue = 0;
    
    this->closeDialog();
}