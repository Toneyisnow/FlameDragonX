//
//  AIMagicAggressiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#include "AIMagicAggressiveDelegate.hpp"
#include "BattleScene.hpp"
#include "CreatureMoveActivity.hpp"

AIMagicAggressiveDelegate::AIMagicAggressiveDelegate(AICreature * creature, BattleScene * scene)
: AIActiveDelegate(creature, scene)
{
    
}

void AIMagicAggressiveDelegate::takeAction()
{
    log("AIMagicAggressiveDelegate for creature %d", _creature->getDefinition()->definitionId);
    
    if (!_creature->isPendingAction())
    {
        this->takeMagicAction();
    }
    else
    {
        this->takePendingAction();
    }
}

void AIMagicAggressiveDelegate::takePendingAction()
{
    // No more magic, just attack the target
    Vector<Creature *> candidateTargets = this->findAttackCandidateTargets();
    if (candidateTargets.size() == 0) {
        _battleScene->waiveTurn(_creature);
        return;
    }
    
    MoveScopeResolver * scopeResolver = new MoveScopeResolver(_battleField, _creature);
    scopeResolver->calculate();
    Vector<FDPoint *> scopePositions = scopeResolver->getResults();
    
    Vec2 reachAttackPosition = this->findReachAttackPosition(scopePositions, candidateTargets);
    log("ReachAttackPosition: %f, %f", reachAttackPosition.x, reachAttackPosition.y);
    
    Vec2 decidedPosition = Vec2(0, 0);
    if (reachAttackPosition != Vec2(0, 0))
    {
        // Found a position could attack a target, go to that position
        decidedPosition = reachAttackPosition;
    }
    else
    {
        // If could not reach attack, use the MovePathResolver to move
        Vec2 candidatePosition = _battleField->getObjectPosition(candidateTargets.at(0));
        decidedPosition = this->findReachMovePosition(scopeResolver, candidatePosition);
    }
    log("decidedPosition: %f, %f", decidedPosition.x, decidedPosition.y);
    
    RoutePoint * route = scopeResolver->getRoutePoint(decidedPosition);
    CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
    _battleScene->getActivityQueue()->appendActivity(activity);
        
    scopeResolver->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIActiveDelegate::takeAttackAction));
    
}

void AIMagicAggressiveDelegate::takeMagicAction()
{
    Vector<MagicDefinition *> availableMagicList = this->getAvailableMagicList();
    if (availableMagicList.size() == 0) {
        _foundAvailableMagic = false;
        _creature->pendingAction();
        return;
    }
    _foundAvailableMagic = true;
    
    Map<MagicDefinition *, Creature *> candidateMagicList = this->getCandidateMagicList(availableMagicList);
    if (candidateMagicList.size() == 0) {
        _foundAvailableTarget = false;
        _creature->pendingAction();
        return;
    }
    _foundAvailableTarget = true;
    
    MagicDefinition * magic = this->chooseMagicFromCandidate(candidateMagicList.keys());
    Vec2 position = this->findOptimizedMagicPosition(magic, candidateMagicList.at(magic));
    
    // Use the magic
    _battleScene->magicTo(_creature, magic->getDefinitionId(), position);
    
}
