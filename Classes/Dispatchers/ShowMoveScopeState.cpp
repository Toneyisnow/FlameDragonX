//
//  ShowMoveScopeState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "ShowMoveScopeState.hpp"
#include "BattleField.hpp"
#include "Creature.hpp"
#include "ScopeIndicator.hpp"
#include "FDPoint.hpp"

ShowMoveScopeState * ShowMoveScopeState::create(BattleScene * scene, StateSession * session)
{
    ShowMoveScopeState * state = new ShowMoveScopeState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

ShowMoveScopeState::ShowMoveScopeState()
{
    
}

ShowMoveScopeState::~ShowMoveScopeState()
{
    
}


void ShowMoveScopeState::onEnterState()
{
    Vec2 position = _session->lastPosition();
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    _battleField->setObjectPosition(creature, position);
    
    _resolver = new MoveScopeResolver(_battleField, creature);
    _resolver->calculate();
    
    Vector<FDPoint *> resultPositions = _resolver->getResults();
    for (int i = 0; i < resultPositions.size(); i++)
    {
        Vec2 pos = resultPositions.at(i)->getValue();
        ScopeIndicator * i1 = new ScopeIndicator();
        _battleField->addObject(i1, pos);
        i1->release();
    }
}

void ShowMoveScopeState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

ActionState * ShowMoveScopeState::handleClickAt(Vec2 position)
{
    return nullptr;
}