//
//  EventLoader.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventLoader.hpp"
#include "EventHandler.hpp"
#include "TurnCondition.hpp"
#include "LocalizedStrings.hpp"
#include "BattleField.hpp"
#include "TalkActivity.hpp"
#include "BattleScene.hpp"

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

int EventLoader::loadSingleEvent(EventCondition * condition, CallbackMethod * method)
{
    FDEvent * event = new FDEvent(++_generatedEventId);
    event->initWithCondition(condition, method);
    
    _eventHandler->addEvent(event);
    
    event->autorelease();
    return event->getEventId();
}

int EventLoader::loadTurnEvent(int turnNumber, CreatureType type, SEL_CALLBACK0 function)
{
    TurnCondition * cond = new TurnCondition(turnNumber, type);
    CallbackMethod * method = new CallbackMethod(this, function);
    
    int eventId = this->loadSingleEvent(cond, method);
    
    cond->release();
    method->release();
    
    return eventId;
}

void EventLoader::showTalkMessage(int chapterId, int conversationId, int sequenceId)
{
    int creatureId = LocalizedStrings::getInstance()->getConversationCreatureId(chapterId, conversationId, sequenceId);
    std::string message =LocalizedStrings::getInstance()->getConversation(chapterId, conversationId, sequenceId);
    
    BattleField * field = _battleScene->getBattleField();
    
    Creature * creature = field->getCreatureById(creatureId);
    
    TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, _battleScene, creature, message);
    _battleScene->getActivityQueue()->appendActivity(talk);
    
}
