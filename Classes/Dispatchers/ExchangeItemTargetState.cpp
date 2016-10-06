//
//  ExchangeItemTargetState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/5/16.
//
//

#include "ExchangeItemTargetState.hpp"

#include "BattleField.hpp"
#include "FDPoint.hpp"
#include "ScopeIndicator.hpp"
#include "CommonHelper.hpp"
#include "BattleScene.hpp"
#include "IdleState.hpp"
#include "ItemMenuState.hpp"
#include "ActionMenuState.hpp"
#include "UsableItemDefinition.hpp"
#include "RangeScopeResolver.hpp"
#include "DataStore.hpp"
#include "CompositeBox.hpp"

ExchangeItemTargetState * ExchangeItemTargetState::create(BattleScene * scene, StateSession * session)
{
    ExchangeItemTargetState * state = new ExchangeItemTargetState();
    state->initWithSession(scene, session);
    state->autorelease();
    
    return state;
}

ExchangeItemTargetState::ExchangeItemTargetState()
{
    
}

ExchangeItemTargetState::~ExchangeItemTargetState()
{
    
}

void ExchangeItemTargetState::onEnterState()
{
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    Vec2 position = _battleField->getObjectPosition(creature);
    RangeScopeResolver * resolver = new RangeScopeResolver(_battleField, position, FDRange::rangeWithValues(1, 1));
    
    Vector<FDPoint *> resultPositions = resolver->calculcate();
    
    for (FDPoint * point : resultPositions)
    {
        Vec2 pos = point->getValue();
        ScopeIndicator * indicator = new ScopeIndicator();
        _battleField->addObject(indicator, pos);
        indicator->release();
    }
    
    resolver->release();
}

void ExchangeItemTargetState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

void ExchangeItemTargetState::handleClickAt(Vec2 position)
{
    if (!CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
    {
        _battleField->setCursorTo(position);
        return;
    }
    
    _creature = _battleField->getCreatureById(_session->selectedCreatureId());
    _itemIndex = _session->selectedItemIndex();
    ItemDefinition * item = _creature->creatureData()->getItem(_itemIndex);
    
    if (_battleField->isPositionInScope(position))
    {
        Creature * target = _battleField->getCreatureAt(position.x, position.y);
        if (target == nullptr || target->getType() != CreatureType_Friend) {
            return;
        }
        
        if (!target->creatureData()->isItemFull()) {
            
            // Give the item to target
            log("Give the item to target.");
            _creature->creatureData()->removeItem(_itemIndex);
            target->creatureData()->addItem(item->getDefinitionId());
            _creature->setTakenAction(true);
            _nextState = ItemMenuState::create(_battleScene, _session);
            return;
        }
        else
        {
            _target = target;
            this->selectItemToExchangeBack();
        }
        
        return;
    }
    else
    {
        _nextState = ItemMenuState::create(_battleScene, _session);
        return;
    }
}

void ExchangeItemTargetState::selectItemToExchangeBack()
{
    CompositeBox * itemBox = new CompositeBox(_target, MessageBoxType_Item, MessageBoxOperatingType_Select);
    itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(ExchangeItemTargetState::confirmItemToExchangeBack));
    _battleScene->getMessageLayer()->showMessage(itemBox);
    itemBox->release();
}

void ExchangeItemTargetState::confirmItemToExchangeBack(int exchangeItemIndex)
{
    if (exchangeItemIndex < 0) {
        return;
    }
    
    log("Exchange the item to target.");
    
    ItemDefinition * item = _creature->creatureData()->getItem(_itemIndex);
    ItemDefinition * exchangeItem = _target->creatureData()->getItem(exchangeItemIndex);
    
    // Give the item to target
    _creature->creatureData()->removeItem(_itemIndex);
    _target->creatureData()->removeItem(exchangeItemIndex);
    _creature->creatureData()->addItem(exchangeItem->getDefinitionId());
    _target->creatureData()->addItem(item->getDefinitionId());
    
    _creature->setTakenAction(true);
    
    _nextState = ItemMenuState::create(_battleScene, _session);
    _battleField->notifyStateDispatcher();

}
