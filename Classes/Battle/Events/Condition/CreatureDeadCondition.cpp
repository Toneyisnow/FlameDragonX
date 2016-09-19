//
//  CreatureDeadCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "CreatureDeadCondition.hpp"


#include "BattleScene.hpp"
#include "BattleField.hpp"

CreatureDeadCondition::CreatureDeadCondition(int creatureId)
{
    _type = EventTypeTriggered;
    
    _creatureId = creatureId;
}

bool CreatureDeadCondition::isMatch(BattleScene * scene)
{
    BattleField * field = scene->getBattleField();
    Creature * creature = field->getDeadCreatureById(_creatureId);
    
    return (creature != nullptr);
}
