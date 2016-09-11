//
//  GameFormula.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/11/16.
//
//

#include "GameFormula.hpp"

FightResult * GameFormula::dealWithFight(BattleField * field, Creature * subject, Creature * target)
{
    FightResult * result = new FightResult(subject, target);
    
    result->autorelease();
    return result;
}

MagicResult * GameFormula::dealWithMagic(BattleField * field, Creature * subject, Vector<Creature * > targets, int magicId)
{
    return nullptr;
}
