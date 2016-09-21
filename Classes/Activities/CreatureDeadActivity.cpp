//
//  CreatureDeadActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CreatureDeadActivity.hpp"
#include "AnimationLibrary.hpp"
#include "BattleField.hpp"

CreatureDeadActivity * CreatureDeadActivity::create(BattleField * field, Creature * creature)
{
    CreatureDeadActivity * activity = new CreatureDeadActivity(field, creature);
    activity->autorelease();
    
    return activity;
}

CreatureDeadActivity::CreatureDeadActivity(BattleField * field, Creature * creature)
: FieldActivity(field)
{
    _creature = creature;
}

void CreatureDeadActivity::initialize()
{
    SlideAnimation * dead = AnimationLibrary::getInstance()->getDeadAnimation(_creature->getDefinition()->animationId);
    
    _creature->setAnimation(dead);
    //// _creature->setActionStatus(ActionStatus_Dead);
}

void CreatureDeadActivity::internalTick(int synchronizedTick)
{
    if (_creature->animationStopped()) {
        _hasFinished = true;
        
        _battleField->getDeadCreatureList()->pushBack(_creature);
        _battleField->removeObject(_creature);
    }
}
