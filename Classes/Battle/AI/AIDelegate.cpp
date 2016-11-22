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

bool AIDelegate::needRecover(Creature * creature)
{
    return (creature->creatureData()->hpCurrent < creature->creatureData()->hpMax);
}

bool AIDelegate::canRecover(Creature * creature)
{
    return this->getRecoverItemIndex(creature) >= 0;
}

int AIDelegate::getRecoverItemIndex(Creature * creature)
{
    for (int index = 0; index < creature->creatureData()->itemList->size(); index++) {
        int itemId = creature->creatureData()->getItem(index)->getDefinitionId();
        if (itemId == 101 || itemId == 102 || itemId == 103 || itemId == 104 || itemId == 122) {
            return index;
        }
    }
    return -1;
}

Creature * AIDelegate::locateNearestFriend()
{
    Vector<Creature *> creatureList = _battleField->getAmicableCreatureList(_creature->getType());
    Creature * target = nullptr;
    int distance = _battleField->getFieldSize().width + _battleField->getFieldSize().height;
    for (Creature * c : creatureList) {
        
        int d = _battleField->getObjectDistance(_creature, c);
        if (d < distance) {
            d = distance;
            target = c;
        }
    }
    
    return target;
}

void AIDelegate::takeWaiveAction()
{
    _battleScene->waiveTurn(_creature);
}


void AIDelegate::setCreatureMoved(Vec2 position)
{
    Vec2 originPosition = _battleField->getObjectPosition(_creature);
    _creature->setMoved(originPosition != position);
}

