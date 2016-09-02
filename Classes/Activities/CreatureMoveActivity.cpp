//
//  CreatureMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "CreatureMoveActivity.hpp"

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
    SimpleMoveActivity * activity = new SimpleMoveActivity(_field, _creature, position);
    this->appendActivity(activity);
    activity->release();
}
