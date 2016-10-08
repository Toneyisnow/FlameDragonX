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
    
}

void AICreature::wakeUpByAttack()
{
    if (aiType == AIType_Idle) {
        aiType = AIType_Aggressive;
    }
}
