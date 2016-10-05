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
#include "CompositeBox.hpp"
#include "CallbackMethod.hpp"
#include "SelectMagicTargetState.hpp"
#include "ItemMenuState.hpp"

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
            this->moveCursorToTarget();
            _nextState = SelectAttackTargetState::create(_battleScene, _session);
            return;
        case 12:
            // Item
            _nextState = ItemMenuState::create(_battleScene, _session);
            return;
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
    CompositeBox * magicBox = new CompositeBox(_creature, MessageBoxType_Magic, MessageBoxOperatingType_Select);
    magicBox->setReturnFunction(this, CALLBACK1_SELECTOR(ActionMenuState::confirmSelectMagic));
    
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
    _nextState = SelectMagicTargetState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();
}

void ActionMenuState::moveCursorToTarget()
{
    Vector<Creature *> targets = _battleField->searchTargetInAttackRange(_creature);
    if (targets.size() == 0)
    {
        return;
    }
    
    _battleField->moveCursorTo(_battleField->getObjectPosition(targets.at(0)));
}

void ActionMenuState::checkTreatureAndWaiveTurn()
{
    Vec2 position = _battleField->getObjectPosition(_creature);
    // Treasure * treasure = _battleField->getTreatureAt(position);
    
    this->confirmPickTreasure();
}

void ActionMenuState::confirmPickTreasure()
{
    _battleField->getBattleScene()->waiveTurn(_creature);
}