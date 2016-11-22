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
: AIActiveDelegate(creature, scene)
{
    
}

void AIAggressiveDelegate::takeAction()
{
    // Locate Targets
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
        Vec2 targetPosition = _battleField->getObjectPosition(candidateTargets.at(0));
        decidedPosition = this->findReachMovePosition(scopeResolver, targetPosition);
    }
    log("decidedPosition: %f, %f", decidedPosition.x, decidedPosition.y);
    
    this->setCreatureMoved(decidedPosition);
    RoutePoint * route = scopeResolver->getRoutePoint(decidedPosition);
    CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
    _battleScene->getActivityQueue()->appendActivity(activity);
    
    scopeResolver->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIActiveDelegate::takeAttackAction));
}

