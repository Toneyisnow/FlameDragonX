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
#include "CallbackActivity.hpp"
#include "CallbackMethod.hpp"

StateDispatcher::StateDispatcher(BattleScene * scene)
{
    _currentState = IdleState::create(scene);
    _currentState->retain();
    
    _scene = scene;
}

StateDispatcher::~StateDispatcher()
{
    
}

void StateDispatcher::onNotified()
{
    if (_currentState == nullptr) {
        return;
    }
    
    ActionState * nextState = _currentState->getNextState();
    if (nextState == nullptr) {
        return;
    }
    
    _currentState->onExitState();
    _currentState->release();
    // CallbackMethod * method1 = CallbackMethod::create(_currentState, CALLBACK0_SELECTOR(ActionState::onExitState));
    // _scene->getActivityQueue()->appendActivity(CallbackActivity::create(method));
    
    _currentState = nextState;
    _currentState->retain();
    
    CallbackMethod * method = CallbackMethod::create(_currentState, CALLBACK0_SELECTOR(ActionState::onEnterState));
    _scene->getActivityQueue()->appendActivity(CallbackActivity::create(method));
}

void StateDispatcher::handleClickAt(Vec2 position)
{
    if (_currentState == nullptr)
    {
        return;
    }
    
    _currentState->handleClickAt(position);
    onNotified();
}

