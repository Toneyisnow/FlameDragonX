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
#include "MenuCursor.hpp"

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
    _battleField->showSystemMenuAt(3, _session->menuPosition);
}

void SystemMenuState::onExitState()
{
    log("Close system menu");
    _battleField->closeMenu();
}

void SystemMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _nextState = IdleState::create(_battleScene);
        return;
    }
    
    if (!menuItem->isSelected())
    {
        if (menuItem->isValid())
        {
            _battleField->setActiveMenuCursor(menuItem);
        }
    }
    
}
