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
    _aiType = AIType_Active;
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
    _isUnnoticeableByOthers = false;
}

void AICreature::wakeUpByAttack()
{
    if (_aiType == AIType_StandBy) {
        _aiType = AIType_Active;
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

bool AICreature::isAbleToAttack(Creature * another)
{
    if (another == nullptr) {
        return false;
    }
    
    AICreature * aiAnother = dynamic_cast<AICreature *>(another);
    if (aiAnother != nullptr && aiAnother->isUnnoticeableByOthers()) {
        return false;
    }
    
    return (this->creatureData()->attackItemIndex >= 0
            && this->creatureData()->calculatedAp() > another->creatureData()->calculatedDp());
}

bool AICreature::isUnnoticeableByOthers()
{
    return _isUnnoticeableByOthers;
}

void AICreature::setUnnoticeableByOthers(bool val)
{
    _isUnnoticeableByOthers = val;
}

void AICreature::startTurn()
{
    Creature::startTurn();
    _isPendingAction = false;
}

void AICreature::pendingAction()
{
    _isPendingAction = true;
}

bool AICreature::isPendingAction()
{
    return _isPendingAction;
}
