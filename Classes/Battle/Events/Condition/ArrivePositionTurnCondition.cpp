//
//  ArrivePositionTurnCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "ArrivePositionTurnCondition.hpp"

#include "BattleScene.hpp"
#include "BattleField.hpp"

ArrivePositionTurnCondition::ArrivePositionTurnCondition(int creatureId, Vec2 position)
: ArrivePositionCondition(creatureId, position)
{
    _type = EventTypeTurn;
}

bool ArrivePositionTurnCondition::isMatch(BattleScene * scene)
{
    return ArrivePositionCondition::isMatch(scene);
}
