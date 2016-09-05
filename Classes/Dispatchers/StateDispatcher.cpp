//
//  ActionDispatcher.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "StateDispatcher.hpp"
#include "IdleState.hpp"
#include "BattleScene.hpp"

StateDispatcher::StateDispatcher(BattleScene * scene)
{
    _currentState = IdleState::create(scene);
    _currentState->retain();
}

StateDispatcher::~StateDispatcher()
{
    
}

void StateDispatcher::handleClickAt(Vec2 position)
{
    if (_currentState == nullptr)
    {
        return;
    }
    
    ActionState * nextState = _currentState->handleClickAt(position);
    
    if (nextState == nullptr) {
        return;
    }
    
    _currentState->onExitState();
    _currentState->release();
    
    _currentState = nextState;
    _currentState->retain();
    _currentState->onEnterState();
    
}

