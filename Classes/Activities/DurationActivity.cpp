//
//  DurationActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/18/16.
//
//

#include "DurationActivity.hpp"
#include "Constants.hpp"

DurationActivity * DurationActivity::create(float duration)
{
    DurationActivity * activity = new DurationActivity(duration);
    activity->autorelease();
    return activity;
}

DurationActivity::DurationActivity(float duration)
{
    _duration = duration;
}

void DurationActivity::initialize()
{
    _tickCount = 0;
}

void DurationActivity::internalTick(int synchronizedTick)
{
    _tickCount ++;
    if (_tickCount >= _duration * Constants::GAME_FPS)
    {
        _hasFinished = true;
    }
}
