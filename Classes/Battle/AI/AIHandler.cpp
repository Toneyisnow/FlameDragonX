//
//  AIFactory.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIHandler.hpp"
#include "BattleScene.hpp"
#include "BattleField.hpp"
#include "Creature.hpp"

#include "AIAggressiveDelegate.hpp"
#include "AIStandByDelegate.hpp"

AIHandler::AIHandler(BattleScene * scene, CreatureType creatureType)
{
    _battleScene = scene;
    _battleField = scene->getBattleField();
    _aiCreatureType = creatureType;
}

AICreature * AIHandler::findNextCreature()
{
    Vector<Creature *> * creatureList = (_aiCreatureType == CreatureType_Enemy) ? _battleField->getEnemyList() : _battleField->getNPCList();
    
    AICreature * target = nullptr;
    int topActionSpeed = 0;
    
    for (Creature * creature : *creatureList) {
        
        AICreature * aiCreature = (AICreature *)creature;
        if (!aiCreature->hasTakenAction() && topActionSpeed < aiCreature->getActionSpeed())
        {
            target = aiCreature;
            topActionSpeed = aiCreature->getActionSpeed();
        }
    }

    return target;
}

void AIHandler::takeAction(AICreature * aiCreature)
{
    AIDelegate * delegate = nullptr;
    
    switch (aiCreature->getAIType()) {
        case AIType_StandBy:
            delegate = new AIStandByDelegate(aiCreature, _battleScene);
            break;
        case AIType_Aggressive:
            delegate = new AIAggressiveDelegate(aiCreature, _battleScene);
            break;
            
        default:
            break;
    }
    
    if (delegate != nullptr)
    {
        delegate->takeAction();
        delegate->autorelease();
    }
    else
    {
        _battleScene->waiveTurn(aiCreature);
    }
}
