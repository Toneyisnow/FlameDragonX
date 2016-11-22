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
#include "LocalizedStrings.hpp"
#include "ConfirmMessage.hpp"
#include "ShowMessageActivity.hpp"
#include "SpeakMessage.hpp"
#include "DataStore.hpp"

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
    _creature->setMoved(_session->creaturePositionAfterMove != _session->creaturePositionBeforeMove);
    
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
        _battleField->closeMenu(true);
        
        if (_creature->hasTakenAction())
        {
            _battleScene->creatureEndTurn(_creature);
            _nextState = IdleState::create(_battleScene);
        }
        else
        {
            _nextState = ShowMoveScopeState::create(_battleScene, _session);
        }
        
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
    
    switch (menuItem->getId()) {
        case 10:
            // Magic
            _battleField->closeMenu(false);
            this->selectMagic();
            break;
        case 11:
            // Attack
            _battleField->closeMenu(true);
            this->moveCursorToAttackTarget();
            _nextState = SelectAttackTargetState::create(_battleScene, _session);
            return;
        case 12:
            // Item
            _battleField->closeMenu(true);
            _nextState = ItemMenuState::create(_battleScene, _session);
            return;
        case 13:
            // Sleep
            _battleField->closeMenu(true);
            checkTreatureAndWaiveTurn();
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
        this->onEnterState();
        return;
    }
    
    _selectedMagic = _creature->creatureData()->getMagic(result);
    _session->setSelectedMagicIndex(result);
    _nextState = SelectMagicTargetState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();
    
    this->moveCursorToMagicTarget();
}

void ActionMenuState::moveCursorToAttackTarget()
{
    Vector<Creature *> targets = _battleField->searchTargetInAttackRange(_creature);
    if (targets.size() == 0)
    {
        return;
    }
    
    _battleField->moveCursorTo(_battleField->getObjectPosition(targets.at(0)));
}

void ActionMenuState::moveCursorToMagicTarget()
{
    Vector<Creature *> targets = _battleField->searchTargetInMagicRange(_creature, _selectedMagic->getDefinitionId());
    if (targets.size() == 0)
    {
        return;
    }
    
    _battleField->moveCursorTo(_battleField->getObjectPosition(targets.at(0)));
}

void ActionMenuState::checkTreatureAndWaiveTurn()
{
    Vec2 position = _battleField->getObjectPosition(_creature);
    Treasure * treasure = _battleField->getTreasureAt(position);
    
    if (treasure == nullptr || treasure->hasOpened()) {
        _battleField->getBattleScene()->waiveTurn(_creature);
        _nextState = IdleState::create(_battleScene);
        
        return;
    }
    
    _treasure = treasure;
    int confirmStringId = (_treasure->boxType() == 3) ? 3 : 2;
    
    ConfirmMessage * confirm = new ConfirmMessage(_creature, LocalizedStrings::getInstance()->getConfirmString(confirmStringId));
    confirm->setReturnFunction(this, CALLBACK1_SELECTOR(ActionMenuState::confirmPickTreasure));
    ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, confirm);
    _battleScene->getActivityQueue()->appendActivity(activity);
    confirm->autorelease();
}

void ActionMenuState::confirmPickTreasure(int confirmed)
{
    _creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (confirmed <= 0) {
        
        // Leave the treasure
        SpeakMessage * message = new SpeakMessage(_creature, LocalizedStrings::getInstance()->getMessageString(2));
        ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, message);
        _battleScene->getActivityQueue()->appendActivity(activity);
        message->release();
        
        _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(ActionMenuState::waiveTurn));
        _nextState = IdleState::create(_battleScene);
        _battleField->notifyStateDispatcher();
        
        return;
    }
    
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(_treasure->itemId());
    
    // Show the Treasure name
    int messageId = (_treasure->boxType() == 3) ? 4 : 3;
    std::string messageString = StringUtils::format(LocalizedStrings::getInstance()->getMessageString(messageId).c_str(), item->getName().c_str());
    SpeakMessage * message = new SpeakMessage(_creature, messageString);
    ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, message);
    _battleScene->getActivityQueue()->appendActivity(activity);
    
    if (!item->isMoney() && _creature->creatureData()->isItemFull()) {
        
        ConfirmMessage * confirm = new ConfirmMessage(_creature, LocalizedStrings::getInstance()->getConfirmString(7));
        confirm->setReturnFunction(this, CALLBACK1_SELECTOR(ActionMenuState::confirmExchangeTreasure));
        ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, confirm);
        _battleScene->getActivityQueue()->appendActivity(activity);
        confirm->autorelease();
    }
    else
    {
        _battleScene->pickupTreasure(_creature);
        _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(ActionMenuState::waiveTurn));
        _nextState = IdleState::create(_battleScene);
        _battleField->notifyStateDispatcher();
        
    }
}

void ActionMenuState::confirmExchangeTreasure(int confirmed)
{
    if (confirmed == 1) {
        
        CompositeBox * box = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Select);
        box->setReturnFunction(this, CALLBACK1_SELECTOR(ActionMenuState::confirmItemToPutBack));
        _battleScene->showMessage(box);
        box->release();
    }
    else {
        // Put it back
        SpeakMessage * message = new SpeakMessage(_creature, LocalizedStrings::getInstance()->getMessageString(2));
        ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, message);
        _battleScene->getActivityQueue()->appendActivity(activity);
        message->release();
        
        _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(ActionMenuState::waiveTurn));
        _nextState = IdleState::create(_battleScene);
        _battleField->notifyStateDispatcher();
    }
}

void ActionMenuState::confirmItemToPutBack(int index)
{
    if (index >= 0) {
        
        ItemDefinition * treasureItem = DataStore::getInstance()->getItemDefinition(_treasure->itemId());
        ItemDefinition * exchangeItem = _creature->creatureData()->getItem(index);
        std::string exchangeItemString = StringUtils::format(LocalizedStrings::getInstance()->getMessageString(6).c_str(), treasureItem->getName().c_str(), exchangeItem->getName().c_str());
        SpeakMessage * message = new SpeakMessage(_creature, exchangeItemString);
        ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, message);
        _battleScene->getActivityQueue()->appendActivity(activity);
        message->release();
        
        _battleScene->exchangeTreasure(_creature, index);
    }
    else {
        
        SpeakMessage * message = new SpeakMessage(_creature, LocalizedStrings::getInstance()->getMessageString(2));
        ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, message);
        _battleScene->getActivityQueue()->appendActivity(activity);
        message->release();
    }
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(ActionMenuState::waiveTurn));
    _nextState = IdleState::create(_battleScene);
    _battleField->notifyStateDispatcher();
}

void ActionMenuState::waiveTurn()
{
    if (_creature != nullptr) {
        _battleScene->waiveTurn(_creature);
    }
}
