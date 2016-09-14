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
#include "SelectAttackTargetState.hpp"
#include "MagicBox.hpp"
#include "CallbackMethod.hpp"

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

void ActionMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _battleField->closeMenu();
        _nextState = ShowMoveScopeState::create(_battleScene, _session);
        return;
    }
    
    if (!menuItem->isSelected())
    {
        if (menuItem->isValid())
        {
            _battleField->setActiveMenuCursor(menuItem);
        }
        
        return;
    }
    
    _battleField->closeMenu();
    switch (menuItem->getId()) {
        case 10:
            // Magic
            this->selectMagic();
            break;
        case 11:
            // Attack
            _nextState = SelectAttackTargetState::create(_battleScene, _session);
            return;
        case 12:
            // Item
            break;
        case 13:
            // Sleep
            checkTreatureAndWaiveTurn();
            _nextState = IdleState::create(_battleScene);
            return;
        default:
            break;
    }
    
}

void ActionMenuState::selectMagic()
{
    MagicBox * magicBox = new MagicBox(_creature, MagicOperatingType_Select);
    SEL_CALLBACK1 k1 = CALLBACK1_SELECTOR(ActionMenuState::confirmSelectMagic);
    magicBox->setReturnFunction(this, k1);
    
    _battleScene->getMessageLayer()->showMessage(magicBox);
}

void ActionMenuState::confirmSelectMagic(int result)
{
    log("Return value from MagicBox: %d", result);
    
    if (result < 0)
    {
        // Cancel
    }
    
    _session->setSelectedMagicIndex(result);
    //// _nextState = SelectMagicTargetState(_battleScene, _session);
    _battleField->notifyStateDispatcher();
}


void ActionMenuState::checkTreatureAndWaiveTurn()
{
    this->confirmPickTreasure();
}

void ActionMenuState::confirmPickTreasure()
{
    _battleField->getBattleScene()->waiveTurn(_creature);
}