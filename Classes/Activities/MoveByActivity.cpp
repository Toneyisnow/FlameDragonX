//
//  MoveByActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#include "MoveByActivity.hpp"


MoveByActivity * MoveByActivity::create(Sprite * sprite, Vec2 byPosition, int tick)
{
    MoveByActivity * action = new MoveByActivity(sprite, byPosition, tick);
    action->autorelease();
    
    return action;
}

MoveByActivity::MoveByActivity(Sprite * sprite, Vec2 byPosition, int tick)
{
    _sprite = sprite;
    _deltaPosition = byPosition;
    _totalTick = (tick > 0) ? tick : 1;
}

void MoveByActivity::internalTick(int synchronizedTick)
{
    _currentTick ++;
    
    float x = _originalPosition.x + (_currentTick * _deltaPosition.x / _totalTick);
    float y = _originalPosition.y + (_currentTick * _deltaPosition.y / _totalTick);
    
    _sprite->setPosition(Vec2(x, y));
    
    if (_currentTick >= _totalTick) {
        _hasFinished = true;
    }
}

void MoveByActivity::initialize()
{
    _originalPosition = _sprite->getPosition();
}
