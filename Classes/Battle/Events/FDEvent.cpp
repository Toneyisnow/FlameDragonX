//
//  FDEvent.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "FDEvent.hpp"

FDEvent::FDEvent(int eventId)
{
    this->_eventId = eventId;
    this->_dependenEvents = new Vector<FDEvent *>();
}

FDEvent::~FDEvent()
{
    this->_dependenEvents->clear();
    delete this->_dependenEvents;
    
    this->_condition->release();
    this->_method->release();
}

void FDEvent::initWithCondition(EventCondition * cond, EventMethod * method)
{
    _isActivated = true;
    this->_condition = cond;
    this->_condition->retain();

    this->_method = method;
    this->_method->retain();
}

bool FDEvent::isTriggered(BattleScene * scene)
{
    bool dependencyDone = true;
    for (int i = 0; i < this->_dependenEvents->size(); i++) {
        FDEvent * event = this->_dependenEvents->at(i);
        if (event != nullptr && event->isActiveEvent())
        {
            dependencyDone = false;
            break;
        }
    }
    
    return dependencyDone && _isActivated && _condition->isMatch(scene);
}

int FDEvent::getEventId()
{
    return _eventId;
}

void FDEvent::doAction()
{
    _isActivated = false;
    
    this->_method->doMethod();
}

void FDEvent::deactivate()
{
    _isActivated = false;
}

void FDEvent::reactivate()
{
    _isActivated = true;
}

bool FDEvent::isActiveEvent()
{
    return _isActivated;
}

void FDEvent::addDependentEvent(FDEvent * other)
{
    this->_dependenEvents->pushBack(other);
}
