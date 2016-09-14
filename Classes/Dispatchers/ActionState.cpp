//
//  ActionState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "ActionState.hpp"
#include "BattleScene.hpp"

ActionState::ActionState()
{
    this->_session = nullptr;
}

void ActionState::initWithSession(BattleScene * scene, StateSession * session)
{
    this->_battleScene  = scene;
    this->_battleField = scene->getBattleField();
    
    this->_session = session;
    this->_session->retain();
    
    _nextState = nullptr;
}

ActionState::~ActionState()
{
    if (_session != nullptr)
    {
        this->_session->release();
    }
}

void ActionState::onEnterState()
{
    
    
}

void ActionState::onExitState()
{
    
}

ActionState * ActionState::getNextState()
{
    return _nextState;
}


void ActionState::handleClickAt(Vec2 position)
{
}