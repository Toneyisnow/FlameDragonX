//
//  CreatureDeadActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CreatureDeadActivity.hpp"

CreatureDeadActivity * CreatureDeadActivity::create(BattleField * field, Creature * creature)
{
    CreatureDeadActivity * activity = new CreatureDeadActivity(field, creature);
    activity->autorelease();
    
    return activity;
}

CreatureDeadActivity::CreatureDeadActivity(BattleField * field, Creature * creature)
: FieldActivity(field)
{
    
}

void CreatureDeadActivity::initialize()
{
    //// _creature->setActionStatus(ActionStatus_Dead);
}

void CreatureDeadActivity::internalTick(int synchronizedTick)
{
    
}
