//
//  TouchHandler.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "TouchHandler.hpp"
#include "BattleField.hpp"
#include "Constants.hpp"

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
     */

    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(TouchHandler::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TouchHandler::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TouchHandler::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(TouchHandler::onTouchEnded, this);
    
    field->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, field);
    _totalTouchCount = 0;
    
    _field = field;
}

void TouchHandler::test()
{
    log("Test");
}

bool TouchHandler::onTouchBegan(Touch* touch, Event* event)
{
    _totalTouchCount ++;
    if (_totalTouchCount > 2) {
        _totalTouchCount = 2;
    }
    /// log("onTouchBegan. %d", _totalTouchCount);
    
    if (_totalTouchCount == 1) {
    
        _firstTouch = touch;
        Point p = touch->getLocation();
        Point fieldPosition = _field->getFieldPositionOnScreen();
    
        _deltaPoint.x = p.x - fieldPosition.x;
        _deltaPoint.y = p.y - fieldPosition.y;
    
        _hasTouchMoved = false;
    }
    else
    {
        _hasTouchMoved = true;
        
        if (_totalTouchCount == 2) {
            _secondTouch = touch;
            
            Point p1 = _firstTouch->getLocation();
            Point p2 = _secondTouch->getLocation();
            float distance = abs(p1.x - p2.x) + abs(p1.y - p2.y) + 1;
            _benchMarkScale = _field->getDisplayScale() / distance;
            _originScale = _field->getDisplayScale();
            _originDistance = distance;
        }
    }
    
    return true;
}

void TouchHandler::onTouchEnded(Touch* touch, Event* event)
{
    /// log("onTouchEnded. %d", _totalTouchCount);
    
    if (_totalTouchCount == 1)
    {
        Vec2 fieldPosition = _field->getFieldPositionOnScreen();
        /// log("%f, %f", fieldPosition.x, fieldPosition.y);
    
        if (!_hasTouchMoved) {
        
            Vec2 p = touch->getLocation();
        
            float scale = _field->getDisplayScale();
            Vec2 positionOnField = Vec2((p.x - fieldPosition.x ) / scale, (p.y - fieldPosition.y) / scale);
            /// log("Position on Field: %f, %f", positionOnField.x, positionOnField.y);
    
            _field->onClickedAt(positionOnField);
        }
        
        _firstTouch = nullptr;
    }
    else if (_totalTouchCount == 2)
    {
        if (touch == _firstTouch) {
            _firstTouch = _secondTouch;
            _secondTouch = nullptr;
        }
        
        Point p = _firstTouch->getLocation();
        Point fieldPosition = _field->getFieldPositionOnScreen();
            
        _deltaPoint.x = p.x - fieldPosition.x;
        _deltaPoint.y = p.y - fieldPosition.y;
    }
    
    _totalTouchCount --;
    
    if (_totalTouchCount < 0) {
        _totalTouchCount = 0;
    }
}

void TouchHandler::onTouchMoved(Touch* touch, Event* event)
{
    /// log("onTouchMoved. %d", _totalTouchCount);
    
    _hasTouchMoved = true;
    
    if (_totalTouchCount == 1) {
        Point p = touch->getLocation();
        this->moveFieldTo(Vec2(p.x - _deltaPoint.x, p.y - _deltaPoint.y));
    }
    else if (_totalTouchCount == 2)
    {
        // Zoom the field
        Point p1 = _firstTouch->getLocation();
        Point p2 = _secondTouch->getLocation();
        float distance = abs(p1.x - p2.x) + abs(p1.y - p2.y) + 1;
        float rate = distance / _originDistance;
        
        _field->setDisplayScale(_originScale * rate);
        
        Point newPos = Vec2(p1.x - _deltaPoint.x * rate, p1.y - _deltaPoint.y * rate);
        this->moveFieldTo(newPos);
    }
}

void TouchHandler::onTouchCancelled(Touch* touch, Event* event)
{
    /// cocos2d::log("touch cancelled");
}

bool TouchHandler::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    log("onTouchesBegan : %d", touches.size());
    
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
        
        if (touches.size() == 2) {
            Point p1 = touches.at(0)->getLocation();
            Point p2 = touches.at(1)->getLocation();
            
            float distance = abs(p1.x - p2.x) + abs(p1.y - p2.y) + 1;
            _benchMarkScale = _field->getDisplayScale() / distance;
        }
    }
    
    return true;
}

void TouchHandler::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    log("onTouchesEnded : %d", touches.size());
    
    Vec2 fieldPosition = _field->getFieldPositionOnScreen();
    log("%f, %f", fieldPosition.x, fieldPosition.y);
    
    if (touches.size() == 1 && !_hasTouchMoved) {
        
        Vec2 p = touches.back()->getLocation();
        
        float scale = _field->getDisplayScale();
        Vec2 positionOnField = Vec2((p.x - fieldPosition.x ) / scale, (p.y - fieldPosition.y) / scale);
        log("Position on Field: %f, %f", positionOnField.x, positionOnField.y);
        
        _field->onClickedAt(positionOnField);
    }
}

void TouchHandler::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    log("onTouchesMoved : %d", touches.size());
    
    _hasTouchMoved = true;
    
    if (touches.size() == 1)
    {
        // Move the field
        Point p = touches.back()->getLocation();
        this->moveFieldTo(Vec2(p.x - _deltaPoint.x, p.y - _deltaPoint.y));
    }
    else if (touches.size() == 2)
    {
        // Zoom the field
        Point p1 = touches.at(0)->getLocation();
        Point p2 = touches.at(1)->getLocation();
        float distance = abs(p1.x - p2.x) + abs(p1.y - p2.y) + 1;
        _field->setDisplayScale(_benchMarkScale * distance);
    }
}

void TouchHandler::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
    log("onTouchesCancelled : %d", touches.size());
    
}

void TouchHandler::moveFieldTo(Vec2 position)
{
    int Move_Margin = Constants::UNIT_ICON_SIZE * _field->getDisplayScale() / 2;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size fieldSize = _field->getFieldSizeOnScreen();
    
    
    float adjustX = position.x - origin.x;
    float adjustY = position.y - origin.y;
    
    float posX = position.x;
    float posY = position.y;
    
    if (fieldSize.width < visibleSize.width - Move_Margin)  // The edge case the the whole map is smaller than screen
    {
        posX = Move_Margin + origin.x;
    }
    else if (adjustX > Move_Margin)
    {
        posX = Move_Margin + origin.x;
    }
    else if (adjustX < visibleSize.width - fieldSize.width - Move_Margin)
    {
        posX = visibleSize.width - fieldSize.width - Move_Margin + origin.x;
    }
    
    if (fieldSize.height < visibleSize.height - Move_Margin)
    {
        posY = Move_Margin + origin.y;
    }
    else if (adjustY > Move_Margin)
    {
        posY = Move_Margin + origin.y;
    }
    else if (adjustY < visibleSize.height - fieldSize.height - Move_Margin)
    {
        posY = visibleSize.height - fieldSize.height - Move_Margin + origin.y;
    }
    
    _field->setFieldPositionOnScreen(posX, posY);
}
