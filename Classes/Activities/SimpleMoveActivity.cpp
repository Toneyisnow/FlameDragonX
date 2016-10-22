//
//  CreatureMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "SimpleMoveActivity.hpp"
#include "BattleField.hpp"
#include "Constants.hpp"

SimpleMoveActivity::SimpleMoveActivity(BattleField * field, BattleObject * object, Vec2 toPosition, float speed)
: FieldActivity(field)
{
    this->_object = object;
    this->_object->retain();
    this->_targetLocation = _battleField->convertPositionToLocation(toPosition);
    this->_speed = speed;
    
}

SimpleMoveActivity::~SimpleMoveActivity()
{
    this->_object->release();
}

void SimpleMoveActivity::initialize()
{
    Vec2 original = _object->getSprite()->getPosition();
    deltaX = 0;
    deltaY = 0;
    
    if (original.x < _targetLocation.x) {
        // Moving right
        this->_object->setDirection(DirectionRight);
        deltaX = 1;
        deltaY = 0;
    }
    else if (original.x > _targetLocation.x) {
        // Moving left
        this->_object->setDirection(DirectionLeft);
        deltaX = -1;
        deltaY = 0;
    }
    else if (original.y < _targetLocation.y) {
        // Moving up
        this->_object->setDirection(DirectionUp);
        deltaX = 0;
        deltaY = 1;
    }
    else if (original.y > _targetLocation.y) {
        // Moving down
        this->_object->setDirection(DirectionDown);
        deltaX = 0;
        deltaY = -1;
    }
}

void SimpleMoveActivity::internalTick(int synchronizeTick)
{
    Vec2 current = _object->getSprite()->getPosition();
    
    float resultX = current.x + deltaX * _speed;
    float resultY = current.y + deltaY * _speed;
    
    if ((resultX - _targetLocation.x) * (current.x - _targetLocation.x) < 0
        || (resultY - _targetLocation.y) * (current.y - _targetLocation.y) < 0
        || (resultX == _targetLocation.x && resultY == _targetLocation.y)) {
        
        _hasFinished = true;
        resultX = _targetLocation.x;
        resultY = _targetLocation.y;
        
        _object->setDirection(DirectionNone);
    }
    
    _object->getSprite()->setPosition(Vec2(resultX, resultY));
}
