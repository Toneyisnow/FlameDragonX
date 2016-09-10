//
//  ActionMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/8/16.
//
//

#include "ActionMenuState.hpp"
#include "BattleField.hpp"
#include "IdleState.hpp"
#include "MenuCursor.hpp"
#include "ShowMoveScopeState.hpp"
#include "BattleScene.hpp"

ActionMenuState * ActionMenuState::create(BattleScene * scene, StateSession * session)
{
    ActionMenuState * state = new ActionMenuState();
    
    state->initWithSession(scene, session);
    state->autorelease();
    
    return state;
}

void ActionMenuState::onEnterState()
{
    log("Show action menu");
    
    _creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    _battleField->showCreatureMenuAt(1, _session->creaturePositionAfterMove, _creature);
}

void ActionMenuState::onExitState()
{
    // _battleField->closeMenu();
}

ActionState * ActionMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        return ShowMoveScopeState::create(_battleScene, _session);
        
    }
    
    if (!menuItem->isSelected())
    {
        if (menuItem->isValid())
        {
            _battleField->setActiveMenuCursor(menuItem);
        }
        
        return nullptr;
    }
    
    _battleField->closeMenu();
    switch (menuItem->getId()) {
        case 10:
            // Magic
            break;
        case 11:
            // Attack
            break;
        case 12:
            // Item
            break;
        case 13:
            // Sleep
            checkTreatureAndWaiveTurn();
            return IdleState::create(_battleScene);
            
        default:
            break;
    }
    
    
    return nullptr;
}

void ActionMenuState::checkTreatureAndWaiveTurn()
{
    this->confirmPickTreasure();
}

void ActionMenuState::confirmPickTreasure()
{
    _battleField->getBattleScene()->waiveTurn(_creature);
}