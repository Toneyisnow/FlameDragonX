//
//  SelectMagicTargetState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/14/16.
//
//

#include "SelectMagicTargetState.hpp"

#include "BattleField.hpp"
#include "FDPoint.hpp"
#include "ScopeIndicator.hpp"
#include "CommonHelper.hpp"
#include "BattleScene.hpp"
#include "IdleState.hpp"
#include "ActionMenuState.hpp"
#include "MagicDefinition.hpp"

SelectMagicTargetState * SelectMagicTargetState::create(BattleScene * scene, StateSession * session)
{
    SelectMagicTargetState * state = new SelectMagicTargetState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

SelectMagicTargetState::SelectMagicTargetState()
{
    
}

SelectMagicTargetState::~SelectMagicTargetState()
{
    
}

void SelectMagicTargetState::onEnterState()
{
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    Vec2 position = _battleField->getObjectPosition(creature);
    int magicIndex = _session->selectedMagicIndex();
    MagicDefinition * magic = creature->creatureData()->getMagic(magicIndex);
    RangeScopeResolver * resolver = new RangeScopeResolver(_battleField, position, magic->getEffectScope());
    
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

void SelectMagicTargetState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

void SelectMagicTargetState::handleClickAt(Vec2 position)
{
    if (!CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
    {
        _battleField->setCursorTo(position);
        return;
    }
    
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    int magicIndex = _session->selectedMagicIndex();
    
    if (_battleField->isPositionInScope(position))
    {
        Vector<Creature *> * targetList = new Vector<Creature *>();
        
        _battleScene->magicTo(creature, magicIndex, targetList);
        _nextState = IdleState::create(_battleScene);
        return;
    }
    else
    {
        _nextState = ActionMenuState::create(_battleScene, _session);
        return;
    }
}
