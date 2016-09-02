//
//  EventLoader.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventLoader.hpp"

EventLoader::EventLoader()
{
    
}

EventLoader::~EventLoader()
{
    
}

void EventLoader::initWithScene(BattleScene * scene)
{
    this->_battleScene = scene;
    _generatedEventId = 0;
}

int EventLoader::loadSingleEvent(EventCondition * condition, void(EventLoader::* callBackMethod)() )
{
    std::function<void()> callback = std::bind(callBackMethod, this);
    
    EventMethod * method = new EventMethod(callback);
    FDEvent * event = new FDEvent(++_generatedEventId);
    event->initWithCondition(condition, method);
    
    return event->getEventId();
}
