//
//  ShowMoveScopeState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "ShowMoveScopeState.hpp"
#include "BattleField.hpp"
#include "BattleScene.hpp"
#include "Creature.hpp"
#include "ScopeIndicator.hpp"
#include "FDPoint.hpp"
#include "CreatureMoveActivity.hpp"
#include "IdleState.hpp"
#include "ActionMenuState.hpp"
#include "CommonHelper.hpp"

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
    Vec2 position = _session->creaturePositionBeforeMove;
    Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
    
    if (creature == nullptr)
    {
        return;
    }
    
    creature->setMoved(false);
    
    /// creature->setFocus(true);
    _battleField->setObjectPosition(creature, position);
    
    _resolver = _session->getMoveScopeResolver();
    if (_resolver == nullptr)
    {
        _resolver = new MoveScopeResolver(_battleField, creature);
        _resolver->calculate();
        _session->setMoveScopeResolver(_resolver);
    }
    
    Vector<FDPoint *> resultPositions = _resolver->getResults();
    
    for (FDPoint * point : resultPositions)
    {
        Vec2 pos = point->getValue();
        ScopeIndicator * indicator = new ScopeIndicator();
        _battleField->addObject(indicator, pos);
        indicator->release();
    }
}

void ShowMoveScopeState::onExitState()
{
    // Remove all of the indicators
    _battleField->removeAllIndicators();
    
}

void ShowMoveScopeState::handleClickAt(Vec2 position)
{
    if (_resolver == nullptr)
    {
        return;
    }
    
    if (!CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
    {
        _battleField->setCursorTo(position);
        return;
    }
    
    if (_battleField->isPositionInScope(position))
    {
        _session->creaturePositionAfterMove = position;
        Creature * creature = _battleField->getCreatureById(_session->selectedCreatureId());
        
        if (position != _session->creaturePositionBeforeMove)
        {
            creature->setMoved(true);
            RoutePoint * routePoint = _resolver->getRoutePoint(position);
            CreatureMoveActivity * move = CreatureMoveActivity::create(_battleField, creature, routePoint);
            _battleField->getBattleScene()->getActivityQueue()->appendActivity(move);
        }
        else
        {
            creature->setMoved(false);
        }
        
        _nextState = ActionMenuState::create(_battleScene, _session);
    }
    else
    {
        _nextState = IdleState::create(_battleScene);
    }
    
}