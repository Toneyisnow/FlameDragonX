//
//  SettingsMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "SettingsMenuState.hpp"

#include "BattleField.hpp"
#include "MenuCursor.hpp"
#include "SystemMenuState.hpp"

SettingsMenuState * SettingsMenuState::create(BattleScene * scene, StateSession * session)
{
    SettingsMenuState * state = new SettingsMenuState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

void SettingsMenuState::onEnterState()
{
    // Show System Menu
    log("Show Settings menu");
    
    Vec2 position = _session->menuPosition;
    _battleField->showSystemMenuAt(5, position);
}

void SettingsMenuState::onExitState()
{
    log("Close Settings menu");
    _battleField->closeMenu();
}

void SettingsMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _nextState = SystemMenuState::create(_battleScene, _session);
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