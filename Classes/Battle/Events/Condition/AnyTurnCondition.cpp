//
//  StartTurnCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "AnyTurnCondition.hpp"
#include "BattleScene.hpp"

AnyTurnCondition::AnyTurnCondition(CreatureType type)
{
    _type = EventTypeTurn;
    
    _turnType = type;
}

bool AnyTurnCondition::isMatch(BattleScene * scene)
{
    return (scene->getCurrentTurnType() == _turnType);
}
