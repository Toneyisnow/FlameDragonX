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

AIAggressiveDelegate::AIAggressiveDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}

void AIAggressiveDelegate::takeAction()
{
    RoutePoint * route = new RoutePoint();
    Vec2 position = _battleField->getObjectPosition(_creature);
    route->appendPoint(Vec2(position.x, position.y + 1));
    route->appendPoint(Vec2(position.x + 1, position.y + 1));
    
    
    // Take Move
    Creature * target = this->locateOffensiveTarget();
    Vec2 targetPosition = this->locateOffensiveTargetPosition(target);
    MovePathResolver * resolver = new MovePathResolver(_battleField, _creature, targetPosition);
    resolver->calculate();
    
    CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, resolver->getRoutePoint());
    _battleScene->getActivityQueue()->appendActivity(activity);
    resolver->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIAggressiveDelegate::takeAttackAction));
}

Creature * AIAggressiveDelegate::locateOffensiveTarget()
{
    Creature * target = nullptr;
    int minDistance = _battleField->getFieldSize().width + _battleField->getFieldSize().height;
    
    if (_creature->getType() == CreatureType_Enemy)
    {
        for (Creature * c : *(_battleField->getFriendList()))
        {
            int distance = _battleField->getObjectDistance(_creature, c);
            if (distance < minDistance)
            {
                target = c;
                minDistance = distance;
            }
        }
        for (Creature * c : *(_battleField->getNPCList()))
        {
            int distance = _battleField->getObjectDistance(_creature, c);
            if (distance < minDistance)
            {
                target = c;
                minDistance = distance;
            }
        }
    }
    else
    {
        for (Creature * c : *(_battleField->getEnemyList()))
        {
            int distance = _battleField->getObjectDistance(_creature, c);
            if (distance < minDistance)
            {
                target = c;
                minDistance = distance;
            }
        }
    }
    
    return target;
}

Vec2 AIAggressiveDelegate::locateOffensiveTargetPosition(Creature * target)
{
    Vec2 targetPosition = _battleField->getObjectPosition(target);
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
    FDRange * attackRange = _creature->getAttackRange();
    int creatureTargetDistance = _battleField->getObjectDistance(_creature, target);
    
    // If the target is far away, just use the target position as result
    if (creatureTargetDistance > _creature->creatureData()->mv + attackRange->getMax()) {
        return targetPosition;
    }
    
    RangeScopeResolver * resolver = new RangeScopeResolver(_battleField, targetPosition, attackRange);
    
    Vector<FDPoint *> resultPositions = resolver->calculcate();
    if (resultPositions.size() == 0)
    {
        return targetPosition;
    }
    
    int maxTargetDistance = 0;
    int minCreatureDistance = creatureTargetDistance + attackRange->getMax();
    Vec2 resultPosition;
    for (FDPoint * point : resultPositions)
    {
        Vec2 pos = point->getValue();
        if (_battleField->getCreatureAt(pos.x, pos.y) != nullptr) {
            continue;
        }
        
        if (ResolverHelper::calculateMovePoint(_battleField, _creature, pos) < 0) {
            continue;
        }
        
        int targetDistance = _battleField->getPositionDistance(pos, targetPosition);
        int creatureDistance = _battleField->getPositionDistance(pos, creaturePosition);
        if (targetDistance > maxTargetDistance)
        {
            maxTargetDistance = targetDistance;
            minCreatureDistance = creatureDistance;
            resultPosition = pos;
        }
        else if (targetDistance == maxTargetDistance)
        {
            if (creatureDistance < minCreatureDistance) {
                minCreatureDistance = creatureDistance;
                resultPosition = pos;
            }
        }
    }
    
    return resultPosition;
}

void AIAggressiveDelegate::takeAttackAction()
{
    
    
    
    
    _battleScene->waiveTurn(_creature);
}
