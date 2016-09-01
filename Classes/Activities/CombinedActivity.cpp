//
//  CombinedActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "CombinedActivity.hpp"

CombinedActivity::CombinedActivity()
{
    this->_activityList = new Vector<FDActivity *>();
}

void CombinedActivity::appendActivity(FDActivity *activity)
{
    this->_activityList->pushBack(activity);
}

void CombinedActivity::initialize()
{
    _currentActivityIndex = 0;
}

void CombinedActivity::internalTick(int synchronizedTick)
{
    if (_currentActivityIndex >= this->_activityList->size())
    {
        _hasFinished = true;
        return;
    }
    
    FDActivity * activity = this->_activityList->at(_currentActivityIndex);
    activity->takeTick(synchronizedTick);
    
    if (activity->hasFinished())
    {
        _currentActivityIndex ++;
    }
    
}


