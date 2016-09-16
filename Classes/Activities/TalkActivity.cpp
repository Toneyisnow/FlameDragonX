//
//  TalkActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "TalkActivity.hpp"
#include "BattleScene.hpp"
#include "TalkMessage.hpp"
#include "SpeakMessage.hpp"

TalkActivity * TalkActivity::create(TalkActivityType type, BattleScene * scene, Creature * creature, std::string message)
{
    TalkActivity * activity = new TalkActivity(type, scene, creature, message);
    activity->autorelease();
    
    return activity;
}

TalkActivity::TalkActivity(TalkActivityType type, BattleScene * scene, Creature * creature, std::string message)
: GlobalActivity(scene)
{
    this->_type = type;
    this->_creature = creature;
    this->_message = message;
}

void TalkActivity::initialize()
{
    log("TalkActivity initialized.");
    
    Message * message;
    
    if (this->_type == TalkActivityType_Speak) {
        message = new SpeakMessage(_creature, _message);
    }
    else {
        // message = new TalkMessage(_creature, _message);
    }
    
    _battleScene->getMessageLayer()->showMessage(message);
    message->release();
}

void TalkActivity::internalTick(int synchronizedTick)
{
    _hasFinished = true;
}
