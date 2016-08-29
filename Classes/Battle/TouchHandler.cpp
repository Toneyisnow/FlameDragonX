//
//  TouchHandler.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "TouchHandler.hpp"
#include "BattleField.hpp"

TouchHandler::TouchHandler(BattleField * field)
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchHandler::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchHandler::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TouchHandler::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(TouchHandler::onTouchCancelled, this);
    
    field->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, field);
    
    _field = field;
}

bool TouchHandler::onTouchBegan(Touch* touch, Event* event)
{
    Point p = touch->getLocation();
    Point fieldPosition = _field->getFieldPositionOnScreen();
    
    _deltaPoint.x = p.x - fieldPosition.x;
    _deltaPoint.y = p.y - fieldPosition.y;
    
    _hasTouchMoved = false;
    
    return true;
}

void TouchHandler::onTouchEnded(Touch* touch, Event* event)
{
    Point fieldPosition = _field->getFieldPositionOnScreen();
    log("%f, %f", fieldPosition.x, fieldPosition.y);
    
}

void TouchHandler::onTouchMoved(Touch* touch, Event* event)
{
    _hasTouchMoved = true;
    Point p = touch->getLocation();
    
    this->moveFieldTo(Vec2(p.x - _deltaPoint.x, p.y - _deltaPoint.y));
}

void TouchHandler::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}

void TouchHandler::moveFieldTo(Vec2 position)
{    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size fieldSize = _field->getFieldSizeOnScreen();
    
    
    float adjustX = position.x - origin.x;
    float adjustY = position.y - origin.y;
    
    float posX = position.x;
    float posY = position.y;
    
    if (adjustX > MOVE_MARGIN_SIZE)
    {
        posX = MOVE_MARGIN_SIZE + origin.x;
    }
    if (adjustY > MOVE_MARGIN_SIZE)
    {
        posY = MOVE_MARGIN_SIZE + origin.y;
    }
    
    if (adjustX < visibleSize.width - fieldSize.width - MOVE_MARGIN_SIZE)
    {
        posX = visibleSize.width - fieldSize.width - MOVE_MARGIN_SIZE + origin.x;
    }
    if (adjustY < visibleSize.height - fieldSize.height - MOVE_MARGIN_SIZE)
    {
        posY = visibleSize.height - fieldSize.height - MOVE_MARGIN_SIZE + origin.y;
    }
    
    _field->setFieldPositionOnScreen(posX, posY);
}