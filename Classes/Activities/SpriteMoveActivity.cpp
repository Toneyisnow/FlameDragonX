//
//  SpriteMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/16/16.
//
//

#include "SpriteMoveActivity.hpp"
#include "Constants.hpp"

SpriteMoveActivity::SpriteMoveActivity(Sprite * object, Vec2 toLocation, float duration)
{
    this->_object = object;
    this->_object->retain();
    this->_targetLocation = toLocation;
    this->_duration = duration;
    
}

SpriteMoveActivity::~SpriteMoveActivity()
{
    this->_object->release();
}

void SpriteMoveActivity::initialize()
{
    auto moveTo = MoveTo::create(_duration, _targetLocation);
    moveTo->setTag(10);
    
    _object->runAction(moveTo);
}

void SpriteMoveActivity::internalTick(int synchronizeTick)
{
    auto moveTo = _object->getActionByTag(10);
    if (moveTo == nullptr)
    {
        _hasFinished = true;
    }
}