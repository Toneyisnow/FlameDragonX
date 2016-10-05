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
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Select);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToExchange));
    _battleScene->getMessageLayer()->showMessage(itemBox);
}

void ItemMenuState::confirmItemToExchange(int itemIndex)
{
    
}

void ItemMenuState::selectItemToUse()
{
    CompositeBox * itemBox = new CompositeBox(_creature, MessageBoxType_Item, MessageBoxOperatingType_Use);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ItemMenuState::confirmItemToUse));
    _battleScene->getMessageLayer()->showMessage(itemBox);
}

void ItemMenuState::confirmItemToUse(int itemIndex)
{
    if (itemIndex < 0) {
        return;
    }
    
    _session->setSelectedItemIndex(itemIndex);
    _nextState = SelectItemTargetState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();
}

void ItemMenuState::selectItemToEquip()
{
    
}

void ItemMenuState::confirmItemToEquip(int itemIndex)
{
    
}

void ItemMenuState::selectItemToDrop()
{
    
}

void ItemMenuState::confirmItemToDrop(int itemIndex)
{
    
}