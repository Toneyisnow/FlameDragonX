//
//  AIDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIDelegate.hpp"
#include "BattleScene.hpp"

AIDelegate::AIDelegate(AICreature * creature, BattleScene * scene)
{
    _creature = creature;
    _battleScene = scene;
    _battleField = scene->getBattleField();
}

void AIDelegate::takeAction()
{
    // Implement in sub class
}
