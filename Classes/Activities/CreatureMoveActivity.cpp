//
//  CreatureMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "CreatureMoveActivity.hpp"
#include "Constants.hpp"
#include "BattleField.hpp"

CreatureMoveActivity * CreatureMoveActivity::create(BattleField * field, int creatureId, RoutePoint * route)
{
    Creature * creature = field->getCreatureById(creatureId);
    return create(field, creature, route);
}

CreatureMoveActivity * CreatureMoveActivity::create(BattleField * field, Creature * creature, RoutePoint * route)
{
    CreatureMoveActivity * activity = new CreatureMoveActivity(field, creature);
    
	for(int i = 0; i < route->getCount(); i++)
	{
		Vec2 point = route->pointAt(i);
		activity->appendPosition(point.x, point.y);
    }
	
    activity->autorelease();
    
    return activity;
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature)
{
    this->_field = field;
    this->_creature = creature;
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, int creatureId)
{
    this->_field = field;
    this->_creature = field->getCreatureById(creatureId);
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
