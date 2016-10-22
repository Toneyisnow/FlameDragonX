//
//  AIAggressiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIAggressiveDelegate.hpp"
#include "BattleScene.hpp"
#include "BattleField.hpp"
#include "CreatureMoveActivity.hpp"
#include "MovePathResolver.hpp"
#include "RangeScopeResolver.hpp"
#include "ResolverHelper.hpp"
#include "MoveScopeResolver.hpp"

AIAggressiveDelegate::AIAggressiveDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}

void AIAggressiveDelegate::takeAction()
{
    // Locate Targets
    Vector<Creature *> candidateTargets = this->locateCandidateTargets();
    if (candidateTargets.size() == 0) {
        _battleScene->waiveTurn(_creature);
        return;
    }
    
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
    MoveScopeResolver * scopeResolver = new MoveScopeResolver(_battleField, _creature);
    scopeResolver->calculate();
    Vector<FDPoint *> scopePositions = scopeResolver->getResults();
    Vec2 reachAttackPosition = Vec2(0, 0);
    FDRange * attackRange = _creature->getAttackRange();
    int maxTargetDistance = 0;
    int minCreatureDistance = _creature->creatureData()->mv;
    
    for (FDPoint * scopePosition : scopePositions) {
        Vec2 pos = scopePosition->getValue();
        
        int creatureDistance = _battleField->getPositionDistance(pos, creaturePosition);
        for (Creature * target : candidateTargets)
        {
            Vec2 targetPosition = _battleField->getObjectPosition(target);
            int targetDistance = _battleField->getPositionDistance(pos, targetPosition);
            
            if (!attackRange->containsValue(targetDistance))
            {
                continue;
            }
            
            if (targetDistance > maxTargetDistance || (targetDistance == maxTargetDistance && creatureDistance < minCreatureDistance))
            {
                reachAttackPosition = pos;
                maxTargetDistance = targetDistance;
                minCreatureDistance = creatureDistance;
            }
        }
    }
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
        Vec2 heuristicPosition = this->locatePathTargetPosition(candidateTargets.at(0));
        log("HeuristicPosition: %f, %f", heuristicPosition.x, heuristicPosition.y);
        
        int minToTarget = _battleField->getPositionDistance(heuristicPosition, creaturePosition);
        int maxMoved = 0;
        for (FDPoint * scopePosition : scopePositions) {
            RoutePoint * route = scopeResolver->getRoutePoint(scopePosition->getValue());
            int movedCount = route->getLength();
            int targetDistance = _battleField->getPositionDistance(heuristicPosition, scopePosition->getValue());
            if (targetDistance < minToTarget || (targetDistance == minToTarget && movedCount > maxMoved)) {
                decidedPosition = scopePosition->getValue();
                minToTarget = targetDistance;
                maxMoved = movedCount;
            }
        }
    }
    log("decidedPosition: %f, %f", decidedPosition.x, decidedPosition.y);
    
    RoutePoint * route = scopeResolver->getRoutePoint(decidedPosition);
    CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
    _battleScene->getActivityQueue()->appendActivity(activity);
    
    scopeResolver->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIAggressiveDelegate::takeAttackAction));
}

Vector<Creature *> AIAggressiveDelegate::locateCandidateTargets()
{
    int minDistance = _battleField->getFieldSize().width + _battleField->getFieldSize().height;
    
    Vector<Creature *> targets;
    if (_creature->getType() == CreatureType_Enemy)
    {
        targets.pushBack(*(_battleField->getFriendList()));
        targets.pushBack(*(_battleField->getNPCList()));
    }
    else
    {
        targets.pushBack(*(_battleField->getEnemyList()));
    }
    
    Vector<Creature *> candidateTargets;
    Creature * candidateTargetOutOfRange = nullptr;
    FDRange * attackRange = _creature->getAttackRange();
    if (attackRange == nullptr) {
        return candidateTargets;
    }
    
    int reachedDistance = _creature->creatureData()->mv + attackRange->getMax();
    for (Creature * c : targets)
    {
        if (!_creature->isAbleToAttack(c)) {
            continue;
        }
        
        int distance = _battleField->getObjectDistance(_creature, c);
        if (distance <= reachedDistance) {
            candidateTargets.pushBack(c);
        }
        else if (distance < minDistance)
        {
            candidateTargetOutOfRange = c;
            minDistance = distance;
        }
    }
    
    if (candidateTargets.size() == 0 && candidateTargetOutOfRange != nullptr) {
        candidateTargets.pushBack(candidateTargetOutOfRange);
    }
    
    return candidateTargets;
}

Vec2 AIAggressiveDelegate::locatePathTargetPosition(Creature * target)
{
    Vec2 targetPosition = _battleField->getObjectPosition(target);
    MovePathResolver * resolver = new MovePathResolver(_battleField, _creature, targetPosition);
    resolver->calculate();
    Vec2 result = resolver->getHeuristicPosition();
    resolver->release();
    
    return result;
}

void AIAggressiveDelegate::takeAttackAction()
{
    FDRange * range = _creature->getAttackRange();
    
    Vector<Creature *> targets = _battleField->getHostileCreatureList(_creature->getType());
    int maxDistance = 0;
    Creature * target = nullptr;
    for (Creature * c : targets) {
        int distance = _battleField->getObjectDistance(_creature, c);
        if (range->containsValue(distance) && _creature->isAbleToAttack(c)) {
            
            if (distance > maxDistance) {
                maxDistance = distance;
                target = c;
            }
        }
    }
    
    if (target != nullptr)
    {
        _battleScene->attackTo(_creature, target);
    }
    else
    {
        // If there is no target found
        _battleScene->waiveTurn(_creature);
    }
}
