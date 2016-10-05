//
//  SelectItemTargetState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/4/16.
//
//

#include "SelectItemTargetState.hpp"

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

SelectItemTargetState * SelectItemTargetState::create(BattleScene * scene, StateSession * session)
{
    SelectItemTargetState * state = new SelectItemTargetState();
    state->initWithSession(scene, session);
    state->autorelease();
    
    return state;
}

SelectItemTargetState::SelectItemTargetState()
{
    
}

SelectItemTargetState::~SelectItemTargetState()
{
    
}

void SelectItemTargetState::onEnterState()
{
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    Vec2 position = _battleField->getObjectPosition(creature);
    int itemIndex = _session->selectedItemIndex();
    ItemDefinition * item = creature->creatureData()->getItem(itemIndex);
    UsableItemDefinition * usableItem = (UsableItemDefinition *)item;
    
    usableItem = (UsableItemDefinition *)DataStore::getInstance()->getItemDefinition(101);
    
    int max = (usableItem->onlyUseToSelf() ? 0 : 1);
    RangeScopeResolver * resolver = new RangeScopeResolver(_battleField, position, FDRange::rangeWithValues(0, max));
    
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

void SelectItemTargetState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

void SelectItemTargetState::handleClickAt(Vec2 position)
{
    if (!CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
    {
        _battleField->setCursorTo(position);
        return;
    }
    
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    int itemIndex = _session->selectedItemIndex();
    
    if (_battleField->isPositionInScope(position))
    {
        Creature * target = _battleField->getCreatureAt(position.x, position.y);
        if (target == nullptr) {
            return;
        }
        
        _battleScene->useItem(creature, itemIndex, target);
        _nextState = IdleState::create(_battleScene);
        return;
    }
    else
    {
        _nextState = ItemMenuState::create(_battleScene, _session);
        return;
    }
}
