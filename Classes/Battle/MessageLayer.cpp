//
//  MessageLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/12/16.
//
//

#include "MessageLayer.hpp"

MessageLayer::MessageLayer(BattleScene * scene)
{
    this->_battleScene = scene;
    
   _listener = EventListenerTouchOneByOne::create();
    
    _listener->onTouchBegan = CC_CALLBACK_2(MessageLayer::onTouchBegan, this);
    _listener->onTouchEnded = CC_CALLBACK_2(MessageLayer::onTouchEnded, this);
    _listener->onTouchMoved = CC_CALLBACK_2(MessageLayer::onTouchMoved, this);
    _listener->onTouchCancelled = CC_CALLBACK_2(MessageLayer::onTouchCancelled, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
    
    _listener->setEnabled(false);
    
    _activeMessage = nullptr;
}

bool MessageLayer::onTouchBegan(Touch* touch, Event* event)
{
    log("TouchBegan on MessageLayer.");
    
    return true;
}

void MessageLayer::onTouchEnded(Touch* touch, Event* event)
{
    log("TouchEnd on MessageLayer");
    
    if (_activeMessage != nullptr)
        this->closeMessage();
}

void MessageLayer::onTouchMoved(Touch* touch, Event* event)
{
    log("TouchMove on MessageLayer");
    
}

void MessageLayer::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled on MessageLayer");
}

bool MessageLayer::isActive()
{
    return (_activeMessage != nullptr);
}

void MessageLayer::showMessage(Message * message)
{
    _activeMessage = message;
    _activeMessage->retain();
    
    _sprite = Sprite::create("Others/MessageBox.png");
    _sprite->setPosition(Vec2(240, 160));
    this->addChild(_sprite);
    
    _listener->setEnabled(true);
    _listener->setSwallowTouches(true);
}
void MessageLayer::closeMessage()
{
    this->removeChild(_sprite);
    
    _activeMessage->release();
    _activeMessage = nullptr;
    
    _listener->setEnabled(false);
    _listener->setSwallowTouches(false);
}