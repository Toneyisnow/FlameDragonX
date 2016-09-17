//
//  TurnCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/16/16.
//
//

#include "TurnCondition.hpp"
#include "BattleScene.hpp"

TurnCondition::TurnCondition(int number, CreatureType type)
{
    _type = EventTypeTurn;
    
    _turnType = type;
    _turnNumber = number;
}

bool TurnCondition::isMatch(BattleScene * scene)
{
    return (scene->getTurnNumber() == _turnNumber && scene->getCurrentTurnType() == _turnType);
}
