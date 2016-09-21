//
//  ShowMessageActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "ShowMessageActivity.hpp"

#include "BattleScene.hpp"
#include "TalkMessage.hpp"
#include "SpeakMessage.hpp"

ShowMessageActivity * ShowMessageActivity::create(BattleScene * scene, Message * message)
{
    ShowMessageActivity * activity = new ShowMessageActivity(scene, message);
    activity->autorelease();
    
    return activity;
}

ShowMessageActivity::ShowMessageActivity(BattleScene * scene, Message * message)
: GlobalActivity(scene)
{
    this->_message = message;
    this->_message->retain();
}

void ShowMessageActivity::initialize()
{
    log("ShowMessageActivity initialized.");

    _battleScene->getMessageLayer()->showMessage(_message);
    _message->release();
}

void ShowMessageActivity::internalTick(int synchronizedTick)
{
    _hasFinished = true;
}