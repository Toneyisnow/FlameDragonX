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
    this->_queuedActivityList = new Vector<FDActivity *>();
    this->_singleActivityList = new Vector<FDActivity *>();
    
    _currentActivity = nullptr;
    _appendToIndex = 0;
}

ActivityQueue::~ActivityQueue()
{
    this->_queuedActivityList->clear();
    delete this->_queuedActivityList;
    
    this->_singleActivityList->clear();
    delete this->_singleActivityList;
}

void ActivityQueue::pushBackActivity(FDActivity * activity)
{
    this->_queuedActivityList->pushBack(activity);
}

void ActivityQueue::insertActivity(FDActivity * activity)
{
    this->_queuedActivityList->insert(0, activity);
}

void ActivityQueue::appendActivity(FDActivity * activity)
{
    this->_queuedActivityList->insert(_appendToIndex, activity);
    _appendToIndex++;
}

void ActivityQueue::insertSingleActivity(FDActivity * activity)
{
    this->_singleActivityList->insert(0, activity);
}

void ActivityQueue::takeTick(int synchronizedTick)
{
    if (_currentActivity == nullptr)
    {
        if (this->_queuedActivityList->size() > 0)
        {
            _currentActivity = this->_queuedActivityList->at(0);
            _currentActivity->retain();
            _appendToIndex = 0;
            
            this->_queuedActivityList->erase(0);
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
    
    for (FDActivity * activity :  *(this->_singleActivityList)) {
        activity->takeTick(synchronizedTick);
        
        if (activity->hasFinished()) {
            this->_singleActivityList->eraseObject(activity);
        }
    }
}
