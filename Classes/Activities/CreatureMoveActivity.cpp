//
//  CreatureMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "CreatureMoveActivity.hpp"
#include "Constants.hpp"

CreatureMoveActivity * CreatureMoveActivity::create(BattleField * field, Creature * creature, RoutePoint * route)
{
    CreatureMoveActivity * activity = new CreatureMoveActivity(field, creature);
    
    activity->appendPosition(0, 0);
    
    activity->autorelease();
    
    return activity;
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature)
{
    this->_field = field;
    this->_creature = creature;
}


void CreatureMoveActivity::appendPosition(int posX, int posY)
{
    this->appendPosition(Vec2(posX, posY));
}

void CreatureMoveActivity::appendPosition(Vec2 position)
{
    SimpleMoveActivity * activity = new SimpleMoveActivity(_field, _creature, position, Constants::CREATURE_MOVE_SPEED);
    this->appendActivity(activity);
    activity->release();
}
