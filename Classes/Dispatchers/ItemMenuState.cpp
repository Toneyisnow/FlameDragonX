//
//  ItemMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/14/16.
//
//

#include "ItemMenuState.hpp"

#include "BattleField.hpp"
#include "IdleState.hpp"
#include "MenuCursor.hpp"
#include "ActionMenuState.hpp"

ItemMenuState * ItemMenuState::create(BattleScene * scene, StateSession * session)
{
    ItemMenuState * state = new ItemMenuState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

void ItemMenuState::onEnterState()
{
    // Show System Menu
    log("Show item menu");
    
    Vec2 position = _session->creaturePositionAfterMove;
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    _battleField->showCreatureMenuAt(2, position, creature);
}

void ItemMenuState::onExitState()
{
    log("Close item menu");
    _battleField->closeMenu();
}

void ItemMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _nextState = ActionMenuState::create(_battleScene, _session);
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
