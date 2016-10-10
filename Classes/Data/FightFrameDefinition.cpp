//
//  FightFrameDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#include "FightFrameDefinition.hpp"

FightFrameDefinition::FightFrameDefinition(int interval, int soundId, bool isRemote, float hittingRate)
{
    _interval = interval;
    _soundId = soundId;
    _isRemote = isRemote;
    _hittingRate = hittingRate;
}

int FightFrameDefinition::interval()
{
    return _interval;
}
int FightFrameDefinition::soundId()
{
    return _soundId;
}

bool FightFrameDefinition::isRemote()
{
    return _isRemote;
}

float FightFrameDefinition::hittingRate()
{
    return _hittingRate;
}
