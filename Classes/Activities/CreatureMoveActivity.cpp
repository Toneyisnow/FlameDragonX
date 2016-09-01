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

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 pos1)
{
    SimpleMoveActivity * activity1 = new SimpleMoveActivity(field, creature, pos1);
    this->appendActivity(activity1);
    activity1->release();
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 pos1, Vec2 pos2)
{
    SimpleMoveActivity * activity1 = new SimpleMoveActivity(field, creature, pos1);
    this->appendActivity(activity1);
    activity1->release();
    SimpleMoveActivity * activity2 = new SimpleMoveActivity(field, creature, pos2);
    this->appendActivity(activity2);
    activity2->release();
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 pos1, Vec2 pos2, Vec2 pos3)
{
    SimpleMoveActivity * activity1 = new SimpleMoveActivity(field, creature, pos1);
    this->appendActivity(activity1);
    activity1->release();
    SimpleMoveActivity * activity2 = new SimpleMoveActivity(field, creature, pos2);
    this->appendActivity(activity2);
    activity2->release();
    SimpleMoveActivity * activity3 = new SimpleMoveActivity(field, creature, pos3);
    this->appendActivity(activity3);
    activity3->release();
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4)
{
    
}

CreatureMoveActivity::CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4, Vec2 pos5)
{
    
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
