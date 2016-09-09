//
//  RemoveObjectActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/8/16.
//
//

#include "RemoveObjectActivity.hpp"

RemoveObjectActivity * RemoveObjectActivity::create(BattleField * field, BattleObject * obj)
{
    RemoveObjectActivity * activity = new RemoveObjectActivity(field, obj);
    activity->autorelease();
    return activity;
}

RemoveObjectActivity::RemoveObjectActivity(BattleField * field, BattleObject * obj)
: FieldActivity(field)
{
    _activity = obj->onRemovalActivity();
    
    if (_activity != nullptr)
    {
        _activity->retain();
    }
}

void RemoveObjectActivity::initialize()
{
    if (_activity != nullptr)
    {
        _activity->initialize();
    }
}

void RemoveObjectActivity::internalTick(int synchronizedTick)
{
    if (_activity != nullptr)
    {
        _activity->takeTick(synchronizedTick);
        if (!_activity->hasFinished()) {
            return;
        }
    }
    
    _battleField->removeObject(obj);
    _hasFinished = true;
}

