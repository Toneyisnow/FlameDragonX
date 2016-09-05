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

ShowMoveScopeState * ShowMoveScopeState::create(BattleScene * scene, StateSession * session)
{
    ShowMoveScopeState * state = new ShowMoveScopeState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
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
    
    ScopeIndicator * i1 = new ScopeIndicator();
    _battleField->addObject(i1, Vec2(position.x, position.y + 1));
    i1->release();
    ScopeIndicator * i2 = new ScopeIndicator();
    _battleField->addObject(i2, Vec2(position.x, position.y - 1));
    i2->release();
    ScopeIndicator * i3 = new ScopeIndicator();
    _battleField->addObject(i3, Vec2(position.x + 1, position.y));
    i3->release();
    ScopeIndicator * i4 = new ScopeIndicator();
    _battleField->addObject(i4, Vec2(position.x - 1, position.y));
    i4->release();
    
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