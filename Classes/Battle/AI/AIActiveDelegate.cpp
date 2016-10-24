//
//  AIActiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#include "AIActiveDelegate.hpp"
#include "BattleField.hpp"
#include "MovePathResolver.hpp"
#include "BattleScene.hpp"
#include "FDRandom.hpp"


AIActiveDelegate::AIActiveDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}


Vector<Creature *> AIActiveDelegate::findAttackCandidateTargets()
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

Vec2 AIActiveDelegate::findReachAttackPosition(Vector<FDPoint *> &scopePositions, Vector<Creature *> &candidateTargets)
{
    Vec2 reachAttackPosition = Vec2(0, 0);
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
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
    
    return reachAttackPosition;
}

Vec2 AIActiveDelegate::findReachMovePosition(MoveScopeResolver * scopeResolver, Vec2 targetPosition)
{
    Vector<FDPoint *> scopePositions = scopeResolver->getResults();
    
    Vec2 decidedPosition = Vec2(0, 0);
    Vec2 heuristicPosition = this->locatePathTargetPosition(targetPosition);
    log("HeuristicPosition: %f, %f", heuristicPosition.x, heuristicPosition.y);
    
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
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
    
    return decidedPosition;
}

Vector<MagicDefinition *> AIActiveDelegate::getAvailableMagicList()
{
    Vector<MagicDefinition *> results;
    
    for (int i = 0; i < _creature->creatureData()->magicList->size(); i++) {
        MagicDefinition * def = _creature->creatureData()->getMagic(i);
        if (def->mpCost() <= _creature->creatureData()->mpCurrent)
        {
            results.pushBack(def);
        }
    }
    
    return results;
}

Map<MagicDefinition *, Creature *> AIActiveDelegate::getCandidateMagicList(Vector<MagicDefinition *> & availableMagics)
{
    Map<MagicDefinition *, Creature *> result;
    
    for (MagicDefinition * magic : availableMagics) {
        
        Creature * target = nullptr;
        if (magic->getType() == MagicType_Attack || magic->getType() == MagicType_Offensive) {
            target = this->findOffensiveTarget(magic);
        }
        else
        {
            target = this->findDefensiveTarget(magic);
        }
        
        if (target != nullptr) {
            result.insert(magic, target);
        }
    }
    
    return result;
}

Creature * AIActiveDelegate::findOffensiveTarget(MagicDefinition * magic)
{
    Vector<Creature *> candidateList = _battleField->getHostileCreatureList(_creature->getType());
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
    Creature * result = nullptr;
    
    for (Creature * c : candidateList)
    {
        if (_battleField->getObjectDistance(c, _creature) <= magic->effectScope() + magic->effectCoverage()) {
            if (result == nullptr || result->creatureData()->hpCurrent > c->creatureData()->hpCurrent) {
                result = c;
            }
        }
    }
    
    return result;
}

Creature * AIActiveDelegate::findDefensiveTarget(MagicDefinition * magic)
{
    Vector<Creature *> candidateList = _battleField->getHostileCreatureList(_creature->getType());
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
    Creature * result = nullptr;
    
    for (Creature * c : candidateList)
    {
        if (magic->isDefensiveUsefulByCreature(c) && _battleField->getObjectDistance(c, _creature) <= magic->effectScope() + magic->effectCoverage()) {
            if (result == nullptr || result->creatureData()->hpCurrent > c->creatureData()->hpCurrent) {
                result = c;
            }
        }
    }
    
    return result;
}

MagicDefinition * AIActiveDelegate::chooseMagicFromCandidate(std::vector<MagicDefinition *> magicList)
{
    int totalConsieration = 0;
    for (MagicDefinition * magic : magicList) {
        totalConsieration += magic->aiConsiderRate();
    }
    
    int ranValue = FDRandom::valueFromRange(1, totalConsieration);
    for (MagicDefinition * magic : magicList) {
        ranValue -= magic->aiConsiderRate();
        if (ranValue <= 0) {
            return magic;
        }
    }
    
    return nullptr;
}

Vec2 AIActiveDelegate::findOptimizedMagicPosition(MagicDefinition * magic, Creature * target)
{
    return Vec2(0, 0);
}

Vec2 AIActiveDelegate::locatePathTargetPosition(Vec2 targetPosition)
{
    MovePathResolver * resolver = new MovePathResolver(_battleField, _creature, targetPosition);
    resolver->calculate();
    Vec2 result = resolver->getHeuristicPosition();
    resolver->release();
    
    return result;
}

void AIActiveDelegate::takeAttackAction()
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
