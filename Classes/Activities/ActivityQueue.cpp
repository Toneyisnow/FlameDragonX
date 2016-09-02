//
//  ActivityQueue.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "ActivityQueue.hpp"

ActivityQueue::ActivityQueue()
{
    this->_activitiList = new Vector<FDActivity *>();
    _currentActivity = nullptr;
    _appendToIndex = 0;
}

ActivityQueue::~ActivityQueue()
{
    this->_activitiList->clear();
    delete this->_activitiList;
}

void ActivityQueue::pushBackActivity(FDActivity * activity)
{
    this->_activitiList->pushBack(activity);
}

void ActivityQueue::insertActivity(FDActivity * activity)
{
    this->_activitiList->insert(0, activity);
}

void ActivityQueue::appendActivity(FDActivity * activity)
{
    this->_activitiList->insert(_appendToIndex, activity);
}

void ActivityQueue::takeTick(int synchronizedTick)
{
    if (_currentActivity == nullptr)
    {
        if (this->_activitiList->size() > 0)
        {
            _currentActivity = this->_activitiList->at(0);
            _currentActivity->retain();
            _appendToIndex = 0;
            
            this->_activitiList->erase(0);
        }
    }
    
    if (_currentActivity != nullptr)
    {
        _currentActivity->takeTick(synchronizedTick);
    }
    
    if (_currentActivity != nullptr && _currentActivity->hasFinished())
    {
        log("Activity has Finished.");
        _currentActivity->release();
        _currentActivity = nullptr;
        _appendToIndex = 0;
    }
    
}
