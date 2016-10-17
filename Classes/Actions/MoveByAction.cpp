//
//  MoveByAction.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#include "MoveByAction.hpp"

MoveByAction * MoveByAction::create(Sprite * sprite, Vec2 byPosition, int tick)
{
    MoveByAction * action = new MoveByAction(sprite, byPosition, tick);
    action->autorelease();
    
    return action;
}

MoveByAction::MoveByAction(Sprite * sprite, Vec2 byPosition, int tick)
: FDAction(sprite)
{
    _deltaPosition = byPosition;
    _totalTick = (tick > 0) ? tick : 1;
    
    _initialized = false;
}

void MoveByAction::takeTick(int synchronizedTick)
{
    if (!_initialized) {
        this->initialize();
        _initialized = true;
    }
    
    _currentTick ++;
    
    float x = _originalPosition.x + (_currentTick * _deltaPosition.x / _totalTick);
    float y = _originalPosition.y + (_currentTick * _deltaPosition.y / _totalTick);
    
    _sprite->setPosition(Vec2(x, y));
    
    if (_currentTick >= _totalTick) {
        _hasFinished = true;
    }
}

void MoveByAction::initialize()
{
    _originalPosition = _sprite->getPosition();
}
