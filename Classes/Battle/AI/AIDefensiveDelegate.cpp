//
//  AIActiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#include "AIDefensiveDelegate.hpp"
#include "MoveScopeResolver.hpp"
#include "CreatureMoveActivity.hpp"
#include "BattleScene.hpp"

AIDefensiveDelegate::AIDefensiveDelegate(AICreature * creature, BattleScene * scene)
: AIActiveDelegate(creature, scene)
{
    
}

void AIDefensiveDelegate::takeAction()
{
    MoveScopeResolver * scopeResolver = new MoveScopeResolver(_battleField, _creature);
    scopeResolver->calculate();
    Vector<FDPoint *> scopePositions = scopeResolver->getResults();
    
    if (this->canRecover(_creature))
    {
        int itemIndex = this->getRecoverItemIndex(_creature);
        
        // Locate Targets
        Creature * candidateTarget = this->findDefensiveCandidateTarget(scopePositions);
        if (candidateTarget != nullptr)
        {
            // Move to and Recover the target
            _defensiveItemIndex = itemIndex;
            _target = candidateTarget;
            
            // Find nearest position
            Vec2 targetPosition = _battleField->getObjectPosition(candidateTarget);
            Vec2 candidatePosition = _battleField->getObjectPosition(_creature);
            int minDistance = _battleField->getPositionDistance(targetPosition, candidatePosition);
            for (FDPoint * point : scopePositions) {
                Vec2 position = point->getValue();
                int dis = _battleField->getPositionDistance(position, targetPosition);
                if (dis < minDistance) {
                    minDistance = dis;
                    candidatePosition = position;
                }
            }
            
            // Make the move
            this->setCreatureMoved(candidatePosition);
            RoutePoint * route = scopeResolver->getRoutePoint(candidatePosition);
            CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
            _battleScene->getActivityQueue()->appendActivity(activity);
            
            
            if (minDistance == 1)
            {
                // Reach the target, use the item
                _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIDefensiveDelegate::useItemToTarget));
            }
            else
            {
                // Cannot reach the target, just wait here
                _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIDelegate::takeWaiveAction));
            }
        }
        else if (this->needRecover(_creature))
        {
            // Recover self
            _battleScene->useItem(_creature, itemIndex, _creature);
            
        }
    }
    else
    {
        Creature * nearestFriend = this->locateNearestFriend();
        
        if (nearestFriend != nullptr) {
            
            // Move to the nearest friend
            Vec2 friendPosition = _battleField->getObjectPosition(nearestFriend);
            Vec2 decidedPosition = this->findReachMovePosition(scopeResolver, friendPosition);
            
            RoutePoint * route = scopeResolver->getRoutePoint(decidedPosition);
            CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
            _battleScene->getActivityQueue()->appendActivity(activity);
            
        }
        else
        {
            // Cannot find any friend, just stand by
            _battleScene->waiveTurn(_creature);
        }
    }
    
    scopeResolver->release();
}

Creature * AIDefensiveDelegate::findDefensiveCandidateTarget(Vector<FDPoint *> &scopePositions)
{
    for (FDPoint * point : scopePositions) {
        Vec2 position = point->getValue();
        Creature * c = _battleField->getCreatureAt(position.x, position.y);
        
        if (c != nullptr && c != _creature && this->needRecover(c)) {
            return c;
        }
    }
    
    return nullptr;
}

void AIDefensiveDelegate::useItemToTarget()
{
    _battleScene->useItem(_creature, _defensiveItemIndex, _target);
}
