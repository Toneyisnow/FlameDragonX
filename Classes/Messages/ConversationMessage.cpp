//
//  ConversationMessage.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "ConversationMessage.hpp"
#include "MessageLayer.hpp"

ConversationMessage::ConversationMessage(std::string content)
: ConversationMessage(nullptr, content)
{
    
}

ConversationMessage::ConversationMessage(Creature * creature, std::string content)
{
    _creature = creature;
    _content = content;
    _upScreen = Vec2(240, 220);
    _downScreen = Vec2(240, 50);
}

void ConversationMessage::initDialog()
{
    buildBaseDialog(_downScreen);
    
}

void ConversationMessage::buildBaseDialog(Vec2 screenPosition)
{
    _messageBox = Sprite::create("Others/MessageBox.png");
    _messageBox->setPosition(screenPosition);
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

void ConversationMessage::removeDialog()
{
    _messageLayer->removeChild(_messageBox);
}

FDActivity * ConversationMessage::onEnterActivity()
{
    return nullptr;
}

FDActivity * ConversationMessage::onExitActivity()
{
    return nullptr;
}

void ConversationMessage::handleClick(Vec2 location)
{
    _returnValue = 0;
    
    this->closeDialog();
}