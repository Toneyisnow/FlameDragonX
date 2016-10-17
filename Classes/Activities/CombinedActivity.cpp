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
    this->_activityList.clear();
}

CombinedActivity::~CombinedActivity()
{
    this->_activityList.clear();
}

void CombinedActivity::appendActivity(FDActivity *activity)
{
    this->_activityList.pushBack(activity);
}

void CombinedActivity::initialize()
{
    _currentActivityIndex = 0;
}

void CombinedActivity::internalTick(int synchronizedTick)
{
    if (_currentActivityIndex >= this->_activityList.size())
    {
        _hasFinished = true;
        return;
    }
    
    FDActivity * activity = this->_activityList.at(_currentActivityIndex);
    activity->takeTick(synchronizedTick);
    
    if (activity->hasFinished())
    {
        _currentActivityIndex ++;
    }
    
}

int CombinedActivity::getTotalTick()
{
    int totalTick = 0;
    for (FDActivity * activity : _activityList)
    {
        totalTick += activity->getTotalTick();
    }
    
    return totalTick;
}

FDActivity * CombinedActivity::getCurrentActivity()
{
    if (_currentActivityIndex >= _activityList.size()) {
        throw new std::exception();
    }
    
    return _activityList.at(_currentActivityIndex);
}

int CombinedActivity::getCurrentIndex()
{
    return _currentActivityIndex;
}

void CombinedActivity::reset()
{
    FDActivity::reset();
    
    for (FDActivity * activity : _activityList)
    {
        activity->reset();
    }
    
    _currentActivityIndex = 0;
}
