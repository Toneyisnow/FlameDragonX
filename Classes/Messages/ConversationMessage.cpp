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
    _upScreen = Vec2(240, 170);
    _downScreen = Vec2(240, 10);
}

void ConversationMessage::initDialog()
{
    buildBaseDialog(_downScreen);
    
}

void ConversationMessage::buildBaseDialog(Vec2 screenPosition)
{
    _messageBox = ScaledSprite::create("Others/MessageBox.png");
    _messageBox->setPosition(screenPosition);
    _messageBox->setAnchorPoint(Vec2(0.5f, 0));
    _messageBox->setScale(Constants::DEFAULT_MESSAGEBOX_SCALE);
    
    this->addChildToLayer(_messageBox);
    
    int creatureDatoId = (_creature != nullptr ? _creature->getDefinition()->animationId : 0);
    Sprite * dato = Sprite::create(StringUtils::format("Dato/Dato-%03d-1.png", creatureDatoId));
    dato->setAnchorPoint(Vec2(0, 0));
    _messageBox->addChild(dato, Vec2(3, 3));
    
    auto label = Label::createWithTTF(_content.c_str(), "fonts/mini_black.ttf", 14);
    label->setColor(Color3B(255, 255, 255));
    label->setAnchorPoint(Vec2(0, 0.5f));
    _messageBox->addLabel(label, Vec2(80, 60));

}

void ConversationMessage::removeDialog()
{
    this->removeChildFromLayer(_messageBox);
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
