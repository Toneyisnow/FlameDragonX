//
//  Enemy.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/17/16.
//
//

#include "Enemy.hpp"

Enemy::Enemy()
: AICreature(CreatureType_Enemy)
{
    
}

Enemy::Enemy(AIType aiType)
: AICreature(CreatureType_Enemy, aiType)
{
    
}

Enemy * Enemy::create(int creatureId, int definitionId)
{
    Enemy * enemy = new Enemy();
    enemy->initWithDefinition(creatureId, definitionId);
    enemy->autorelease();
    return enemy;
}

Enemy * Enemy::create(int creatureId, int definitionId, int dropItemId)
{
    Enemy * enemy = new Enemy();
    enemy->initWithDefinition(creatureId, definitionId);
    enemy->dropItemId = dropItemId;
    
    enemy->autorelease();
    return enemy;
}


