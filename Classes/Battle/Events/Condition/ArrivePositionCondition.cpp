//
//  ArrivePositionCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "ArrivePositionCondition.hpp"

#include "BattleScene.hpp"
#include "BattleField.hpp"

ArrivePositionCondition::ArrivePositionCondition(int creatureId, Vec2 position)
{
    _type = EventTypeTriggered;
    
    _creatureId = creatureId;
    _targetPosition = position;
}

bool ArrivePositionCondition::isMatch(BattleScene * scene)
{
    BattleField * field = scene->getBattleField();
    Creature * creature = field->getCreatureAt(_targetPosition.x, _targetPosition.y);
    
    return (creature != nullptr && (_creatureId == 0 || _creatureId == creature->getId()));
}
