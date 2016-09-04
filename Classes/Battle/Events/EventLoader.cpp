//
//  EventLoader.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventLoader.hpp"
#include "EventHandler.hpp"

EventLoader::EventLoader()
{
    
}

EventLoader::~EventLoader()
{
    
}

void EventLoader::loadEvents()
{
    
}

void EventLoader::initWithScene(BattleScene * scene, EventHandler * handler)
{
    this->_battleScene = scene;
    this->_eventHandler = handler;
    
    _generatedEventId = 0;
}

int EventLoader::loadSingleEvent(EventCondition * condition, void(EventLoader::* callBackMethod)() )
{
    std::function<void()> callback = std::bind(callBackMethod, this);
    
    CallbackMethod * method = new CallbackMethod(callback);
    FDEvent * event = new FDEvent(++_generatedEventId);
    event->initWithCondition(condition, method);
    
    _eventHandler->addEvent(event);
    
    method->release();
    event->release();
    return event->getEventId();
}
