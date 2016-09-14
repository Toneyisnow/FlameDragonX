//
//  SelectAttackTargetState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "SelectAttackTargetState.hpp"
#include "BattleField.hpp"
#include "FDPoint.hpp"
#include "ScopeIndicator.hpp"
#include "CommonHelper.hpp"
#include "BattleScene.hpp"
#include "IdleState.hpp"
#include "ActionMenuState.hpp"


SelectAttackTargetState * SelectAttackTargetState::create(BattleScene * scene, StateSession * session)
{
    SelectAttackTargetState * state = new SelectAttackTargetState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

SelectAttackTargetState::SelectAttackTargetState()
{
    
}

SelectAttackTargetState::~SelectAttackTargetState()
{
    
}


void SelectAttackTargetState::onEnterState()
{
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    Vec2 position = _battleField->getObjectPosition(creature);
    RangeScopeResolver * resolver = new RangeScopeResolver(_battleField, position, creature->getAttackRange());
    
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

void SelectAttackTargetState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

void SelectAttackTargetState::handleClickAt(Vec2 position)
{
    if (!CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
    {
        _battleField->setCursorTo(position);
        return;
    }
    
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (_battleField->isPositionInScope(position))
    {
        Creature * target = _battleField->getCreatureAt(position.x, position.y);
        
        if (target != nullptr && target->getType() == CreatureType_Enemy)
        {
            _battleScene->attackTo(creature, target);
            _nextState = IdleState::create(_battleScene);
            return;
        }
    }
    else
    {
        _nextState = ActionMenuState::create(_battleScene, _session);
        return;
    }
}
