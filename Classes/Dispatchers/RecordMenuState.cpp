//
//  RecordMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "RecordMenuState.hpp"

#include "BattleField.hpp"
#include "MenuCursor.hpp"
#include "SystemMenuState.hpp"

RecordMenuState * RecordMenuState::create(BattleScene * scene, StateSession * session)
{
    RecordMenuState * state = new RecordMenuState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

void RecordMenuState::onEnterState()
{
    // Show System Menu
    log("Show record menu");
    
    Vec2 position = _session->menuPosition;
    _battleField->showSystemMenuAt(4, position);
}

void RecordMenuState::onExitState()
{
    log("Close record menu");
    _battleField->closeMenu(true);
}

void RecordMenuState::handleClickAt(Vec2 position)
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
