//
//  EventHandler.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventHandler.hpp"
#include "EventLoaderFactory.hpp"
#include "BattleScene.hpp"
#include "EventLoader.hpp"

EventHandler::EventHandler(BattleScene * scene)
{
    this->_battleScene = scene;
    this->_eventList = new Vector<FDEvent *>();
}

EventHandler::~EventHandler()
{
    this->_eventList->clear();
    delete this->_eventList;
    _eventLoader->release();
    
}

void EventHandler::initFromDefinition(int chapterId)
{
    _eventLoader = EventLoaderFactory::getEventLoader(chapterId);
    _eventLoader->initWithScene(this->_battleScene, this);
    _eventLoader->loadEvents();
    
    _eventLoader->retain();
}


void EventHandler::addEvent(FDEvent * event)
{
    this->_eventList->pushBack(event);
}

void EventHandler::deactiveEvent(int eventId)
{
    for (int i= 0; i < this->_eventList->size(); i++) {
        FDEvent * event = this->_eventList->at(i);
        if (event->getEventId() == eventId)
        {
            event->deactivate();
        }
    }
}

void EventHandler::reactiveEvent(int eventId)
{
    for (int i= 0; i < this->_eventList->size(); i++) {
        FDEvent * event = this->_eventList->at(i);
        if (event->getEventId() == eventId)
        {
            event->reactivate();
        }
    }
}

void EventHandler::setDependentEvent(int eventId, int dependOnEventId)
{
    FDEvent * target = nullptr;
    FDEvent * dependent = nullptr;
    
    for (int i= 0; i < this->_eventList->size(); i++) {
        FDEvent * event = this->_eventList->at(i);
        if (event->getEventId() == eventId)
        {
            target = event;
        }
        if (event->getEventId() == dependOnEventId)
        {
            dependent = event;
        }
    }
    
    if (target != nullptr && dependent != nullptr)
    {
        target->addDependentEvent(dependent);
    }
}

void EventHandler::notifyTurnEvents()
{
    for (int i= 0; i < this->_eventList->size(); i++)
    {
        FDEvent * event = this->_eventList->at(i);
        if (event->getType() == EventTypeTurn && event->isTriggered(_battleScene))
        {
            log("Event is triggered.");
            event->doAction();
        }
    }
}

void EventHandler::notifyTriggeredEvents()
{
    for (int i= 0; i < this->_eventList->size(); i++)
    {
        FDEvent * event = this->_eventList->at(i);
        if (event->getType() == EventTypeTriggered && event->isTriggered(_battleScene))
        {
            log("Event is triggered.");
            event->doAction();
        }
    }
}