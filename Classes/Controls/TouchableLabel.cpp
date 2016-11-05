//
//  TouchableLabel.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/1/16.
//
//

#include "TouchableLabel.hpp"

TouchableLabel* TouchableLabel::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions /* = Size::ZERO */, enum TextHAlignment hAlignment /* = TextHAlignment::LEFT */, enum TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new (std::nothrow) TouchableLabel(hAlignment,vAlignment);
    
    if (ret && ret->initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

TouchableLabel::TouchableLabel(enum TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
               enum TextVAlignment vAlignment /* = TextVAlignment::TOP */)
: Label(hAlignment, vAlignment)
{
    _callbackObject = nullptr;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchableLabel::onLabelTouchBegin, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchableLabel::onLabelTouched, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

}

void TouchableLabel::setCallback(Ref * obj, SEL_CALLBACK1 callback)
{
    _callbackObject = obj;
    _callbackMethod = callback;
}


bool TouchableLabel::onLabelTouchBegin(Touch* touch, Event* event)
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

void TouchableLabel::onLabelTouched(Touch* touch, Event* event)
{
    int tag = event->getCurrentTarget()->getTag();
    
    if (_callbackObject != nullptr) {
        CallbackMethod * method = CallbackMethod::create(_callbackObject, _callbackMethod, tag);
        method->execute();
    }
}
