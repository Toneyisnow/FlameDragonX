//
//  TouchableSprite.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "TouchableSprite.hpp"

TouchableSprite* TouchableSprite::create(const std::string& filename)
{
    TouchableSprite *sprite = new (std::nothrow) TouchableSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool TouchableSprite::initWithFile(const std::string& filename)
{
    ScaledSprite::initWithFile(filename);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchableSprite::onSpriteTouchBegin, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchableSprite::onSpriteTouched, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void TouchableSprite::setCallback(Ref * obj, SEL_CALLBACK0 callback)
{
    _callbackObject = obj;
    _callbackMethod0 = callback;
}

void TouchableSprite::setCallback(Ref * obj, SEL_CALLBACK1 callback)
{
    _callbackObject = obj;
    _callbackMethod1 = callback;
}

bool TouchableSprite::onSpriteTouchBegin(Touch* touch, Event* event)
{
    // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    //Get the position of the current point relative to the button
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    //Check the click area
    if (rect.containsPoint(locationInNode))
    {
        return true;
    }
    
    return false;
}

void TouchableSprite::onSpriteTouched(Touch* touch, Event* event)
{
    int tag = event->getCurrentTarget()->getTag();
    
    if (_callbackObject != nullptr && _callbackMethod0 != nullptr) {
        CallbackMethod * method = CallbackMethod::create(_callbackObject, _callbackMethod0);
        method->execute();
    }
    if (_callbackObject != nullptr && _callbackMethod1 != nullptr) {
        CallbackMethod * method = CallbackMethod::create(_callbackObject, _callbackMethod1, tag);
        method->execute();
    }
}
