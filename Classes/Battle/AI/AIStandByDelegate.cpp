//
//  AIIdleDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIStandByDelegate.hpp"
#include "BattleScene.hpp"

AIStandByDelegate::AIStandByDelegate(AICreature * creature, BattleScene * scene)
: AIDelegate(creature, scene)
{
    
}

void AIStandByDelegate::takeAction()
{
    _battleScene->waiveTurn(_creature);
}
