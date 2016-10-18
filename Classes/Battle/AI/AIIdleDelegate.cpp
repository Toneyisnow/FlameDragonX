//
//  AIIdleDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIIdleDelegate.hpp"
#include "BattleScene.hpp"

AIIdleDelegate::AIIdleDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}

void AIIdleDelegate::takeAction()
{
    _battleScene->waiveTurn(_creature);
}
