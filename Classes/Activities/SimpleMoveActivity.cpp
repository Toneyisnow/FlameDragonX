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

SimpleMoveActivity::SimpleMoveActivity(BattleField * field, Creature * creature, Vec2 toPosition)
: FieldActivity(field)
{
    this->_creature = creature;
    this->_targetLocation = _battleField->convertPositionToLocation(toPosition);
    this->_speed = Constants::DEFAULT_MOVE_SPEED;
    
}

void SimpleMoveActivity::initialize()
{
    Vec2 original = _creature->getSprite()->getPosition();
    
    if (original.x < _targetLocation.x) {
        // Moving right
        this->_creature->setGesture(GestureStatus_WalkingRight);
        deltaX = 1;
        deltaY = 0;
    }
    else if (original.x > _targetLocation.x) {
        // Moving left
        this->_creature->setGesture(GestureStatus_WalkingLeft);
        deltaX = -1;
        deltaY = 0;
    }
    else if (original.y < _targetLocation.y) {
        // Moving up
        this->_creature->setGesture(GestureStatus_WalkingUp);
        deltaX = 0;
        deltaY = 1;
    }
    else if (original.y > _targetLocation.y) {
        // Moving down
        this->_creature->setGesture(GestureStatus_WalkingDown);
        deltaX = 0;
        deltaY = -1;
    }
}

void SimpleMoveActivity::internalTick(int synchronizeTick)
{
    Vec2 current = this->_creature->getSprite()->getPosition();
    
    float resultX = current.x + deltaX * _speed;
    float resultY = current.y + deltaY * _speed;
    
    if ((resultX - _targetLocation.x) * (current.x - _targetLocation.x) < 0
        || (resultY - _targetLocation.y) * (current.y - _targetLocation.y) < 0
        || (resultX == _targetLocation.x && resultY == _targetLocation.y)) {
        
        _hasFinished = true;
        resultX = _targetLocation.x;
        resultY = _targetLocation.y;
        
        this->_creature->setGesture(GestureStatus_Idle);
    }
    
    this->_creature->getSprite()->setPosition(Vec2(resultX, resultY));
}
