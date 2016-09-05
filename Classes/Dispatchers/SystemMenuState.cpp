//
//  SystemMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "SystemMenuState.hpp"
#include "BattleField.hpp"
#include "IdleState.hpp"

SystemMenuState * SystemMenuState::create(BattleScene * scene, StateSession * session)
{
    SystemMenuState * state = new SystemMenuState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

void SystemMenuState::onEnterState()
{
    // Show System Menu
    log("Show system menu");
    _battleField->showMenuAt(3, _session->lastPosition());
}

void SystemMenuState::onExitState()
{
    log("Close system menu");
    _battleField->closeMenu();
}

ActionState * SystemMenuState::handleClickAt(Vec2 position)
{
    return IdleState::create(_battleScene);
}
