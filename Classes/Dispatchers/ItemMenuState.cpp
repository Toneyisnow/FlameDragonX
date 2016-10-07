//
//  ItemMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/14/16.
//
//

#include "ItemMenuState.hpp"

#include "BattleField.hpp"
#include "BattleScene.hpp"
#include "IdleState.hpp"
#include "MenuCursor.hpp"
#include "ActionMenuState.hpp"
#include "CompositeBox.hpp"
#include "SelectItemTargetState.hpp"
#include "ExchangeItemTargetState.hpp"

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
    _creature = _battleField->getCreatureById(_session->selectedCreatureId());
    _battleField->showCreatureMenuAt(2, position, _creature);
}

void ItemMenuState::onExitState()
{
    log("Close item menu");
    // _battleField->closeMenu(true);
}

void ItemMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _battleField->closeMenu(true);
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
    
    switch (menuItem->getId()) {
        case 20:
            // Exchange Item
            this->selectItemToExchange();
            break;
        case 21:
            // Use Item
            this->selectItemToUse();
            break;
        case 22:
            // Equip Item
            this->selectItemToEquip();
            break;
        case 23:
            // Drop Item
            this->selectItemToDrop();
            break;
            
        default:
            break;
    }
}

void ItemMenuState::selectItemToExchange()
{
    _battleField->closeMenu(false);
    
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Select);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToExchange));
    _battleScene->getMessageLayer()->showMessage(itemBox);
    itemBox->release();
}

void ItemMenuState::confirmItemToExchange(int itemIndex)
{
    if (itemIndex < 0) {
        
        this->onEnterState();
        return;
    }
    
    _session->setSelectedItemIndex(itemIndex);
    _nextState = ExchangeItemTargetState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();
}

void ItemMenuState::selectItemToUse()
{
    _battleField->closeMenu(false);
    
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Use);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToUse));
    _battleScene->getMessageLayer()->showMessage(itemBox);
    itemBox->release();
}

void ItemMenuState::confirmItemToUse(int itemIndex)
{
    if (itemIndex < 0) {
        this->onEnterState();
        return;
    }
    
    _session->setSelectedItemIndex(itemIndex);
    _nextState = SelectItemTargetState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();
}

void ItemMenuState::selectItemToEquip()
{
    _battleField->closeMenu(false);
    
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Equip);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToEquip));
    _battleScene->getMessageLayer()->showMessage(itemBox);
    itemBox->release();
}

void ItemMenuState::confirmItemToEquip(int itemIndex)
{
    this->onEnterState();
}

void ItemMenuState::selectItemToDrop()
{
    _battleField->closeMenu(false);
    
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Select);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToDrop));
    _battleScene->getMessageLayer()->showMessage(itemBox);
    itemBox->release();

}

void ItemMenuState::confirmItemToDrop(int itemIndex)
{
    this->onEnterState();
    
    if (itemIndex >= 0) {
        
        // Drop Item
        _creature->creatureData()->removeItem(itemIndex);
    }
}
