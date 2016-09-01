//
//  BatchActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "BatchActivity.hpp"

BatchActivity::BatchActivity()
{
    this->_activityList = new Vector<FDActivity *>();
}

BatchActivity::~BatchActivity()
{
    this->_activityList->clear();
    delete this->_activityList;
}

void BatchActivity::addActivity(FDActivity *activity)
{
    this->_activityList->pushBack(activity);
}

void BatchActivity::initialize()
{
    
}

void BatchActivity::internalTick(int synchronizedTick)
{
    bool finished = true;
    for (int i = 0; i < this->_activityList->size(); i++) {
        FDActivity * activity = this->_activityList->at(i);
        activity->takeTick(synchronizedTick);
        
        if (!activity->hasFinished())
        {
            finished = false;
        }
    }
    
    if (finished)
    {
        _hasFinished = true;
    }
}
