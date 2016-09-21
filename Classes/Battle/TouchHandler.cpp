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
	/*
	
	Multi touch
	
	- application:application didFinishLaunchingWithOptions:launchOptions 
{
     // Override point for customization after application launch.
    // Add the view controller’s view to the window and display.
    window = initWithFrame: bounds]];
    EAGLView \**glView = [EAGLView viewWithFrame: [window bounds]
    pixelFormat: kEAGLColorFormatRGBA8
    depthFormat: GL\_DEPTH\_COMPONENT16\_OES
    preserveBackbuffer: NO
    sharegroup: nil
    multiSampling: NO
    numberOfSamples: 0 ];
[_glView setMultipleTouchEnabled:YES]; // enable multi-touch here![]() It’s at about line 37
// …
return YES;

*/
    
auto listener = EventListenerTouchAllAtOnce::create();
listener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event* evt) {
    this->onTouchesBegan(touches, evt);
    // auto last = touches.back();
 // check if last touch point is in which button
};

listener->onTouchesCancelled = [&](const std::vector<Touch*>& touches, Event* evt) {
    this->onTouchesCancelled(touches, evt);
};
    
listener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event* evt) {
    this->onTouchesEnded(touches, evt);
};
    
listener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event* evt) {
    this->onTouchesMoved(touches, evt);
};

field->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);


	
	
	
	/*
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchHandler::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchHandler::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TouchHandler::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(TouchHandler::onTouchCancelled, this);
    
    field->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, field);
    */
    
    _field = field;
}

void TouchHandler::test()
{
    log("Test");
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
    Vec2 fieldPosition = _field->getFieldPositionOnScreen();
    log("%f, %f", fieldPosition.x, fieldPosition.y);
    
    if (!_hasTouchMoved) {
        
        Vec2 p = touch->getLocation();
        
        float scale = _field->getDisplayScale();
        Vec2 positionOnField = Vec2((p.x - fieldPosition.x ) / scale, (p.y - fieldPosition.y) / scale);
        log("Position on Field: %f, %f", positionOnField.x, positionOnField.y);
    
        _field->onClickedAt(positionOnField);
    }
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

bool TouchHandler::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    Point p = touches.back()->getLocation();
    Point fieldPosition = _field->getFieldPositionOnScreen();
    
    _deltaPoint.x = p.x - fieldPosition.x;
    _deltaPoint.y = p.y - fieldPosition.y;
    
    if (touches.size() == 1)
    {
        _hasTouchMoved = false;
    }
    else
    {
        _hasTouchMoved = true;
    }
    
    return true;
}

void TouchHandler::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    Vec2 fieldPosition = _field->getFieldPositionOnScreen();
    log("%f, %f", fieldPosition.x, fieldPosition.y);
    
    if (!_hasTouchMoved) {
        
        Vec2 p = touches.back()->getLocation();
        
        float scale = _field->getDisplayScale();
        Vec2 positionOnField = Vec2((p.x - fieldPosition.x ) / scale, (p.y - fieldPosition.y) / scale);
        log("Position on Field: %f, %f", positionOnField.x, positionOnField.y);
        
        _field->onClickedAt(positionOnField);
    }
}

void TouchHandler::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    _hasTouchMoved = true;
    Point p = touches.back()->getLocation();
    
    this->moveFieldTo(Vec2(p.x - _deltaPoint.x, p.y - _deltaPoint.y));
}

void TouchHandler::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
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