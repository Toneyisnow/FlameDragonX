//
//  TalkActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "TalkActivity.hpp"

TalkActivity * TalkActivity::create(BattleScene * scene, Creature * creature, std::string message)
{
    TalkActivity * activity = new TalkActivity(scene, creature, message);
    activity->autorelease();
    
    return activity;
}

TalkActivity::TalkActivity(BattleScene * scene, Creature * creature, std::string message)
: GlobalActivity(scene)
{
    this->_creature = creature;
    this->_message = message;
}

void TalkActivity::initialize()
{
    log("TalkActivity initialized.");
}

void TalkActivity::internalTick(int synchronizedTick)
{
    _hasFinished = true;
}
