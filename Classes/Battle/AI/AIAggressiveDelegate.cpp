//
//  AIAggressiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIAggressiveDelegate.hpp"
#include "BattleScene.hpp"
#include "CreatureMoveActivity.hpp"

AIAggressiveDelegate::AIAggressiveDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}

void AIAggressiveDelegate::takeAction()
{
    // Take Move
    RoutePoint * route = new RoutePoint();
    Vec2 position = _battleField->getObjectPosition(_creature);
    route->appendPoint(Vec2(position.x, position.y + 1));
    route->appendPoint(Vec2(position.x + 1, position.y + 1));
    
    CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
    _battleScene->getActivityQueue()->appendActivity(activity);
    route->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK0_SELECTOR(AIAggressiveDelegate::searchAttackTarget));
}

void AIAggressiveDelegate::searchAttackTarget()
{
    _battleScene->waiveTurn(_creature);
}
