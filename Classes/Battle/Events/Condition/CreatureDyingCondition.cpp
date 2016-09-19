//
//  CreatureDyingCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "CreatureDyingCondition.hpp"

#include "BattleScene.hpp"
#include "BattleField.hpp"

CreatureDyingCondition::CreatureDyingCondition(int creatureId)
{
    _type = EventTypeTriggered;
    
    _creatureId = creatureId;
}

bool CreatureDyingCondition::isMatch(BattleScene * scene)
{
    BattleField * field = scene->getBattleField();
    Creature * creature = field->getCreatureById(_creatureId);
    
    return (creature != nullptr && creature->creatureData()->hpCurrent <= 0);
}
