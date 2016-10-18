//
//  AICreatureData.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#include "AICreature.hpp"


AICreature::AICreature(CreatureType type)
: Creature(type)
{
    _aiType = AIType_Aggressive;
}

AICreature::AICreature(CreatureType type, AIType aiType)
: Creature(type)
{
    _aiType = aiType;
}

void AICreature::initWithDefinition(int identity, int creatureId)
{
    Creature::initWithDefinition(identity, creatureId);
    
    this->generateActionSpeed();
}

void AICreature::wakeUpByAttack()
{
    if (_aiType == AIType_Idle) {
        _aiType = AIType_Aggressive;
    }
}

AIType AICreature::getAIType()
{
    return _aiType;
}

void AICreature::generateActionSpeed()
{
    // TODO: should add more logic here
    
    if (this->knowMagic()) {
        _actionSpeed = 20;
    }
    else {
        _actionSpeed = 10;
    }
}

int AICreature::getActionSpeed()
{
    return _actionSpeed;
}
