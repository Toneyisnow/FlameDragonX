//
//  GameFormula.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/11/16.
//
//

#ifndef GameFormula_hpp
#define GameFormula_hpp

#include "cocos2d.h"
#include "FightResult.hpp"
#include "MagicResult.hpp"

class BattleField;

class GameFormula : public cocos2d::Ref
{
    
private:
    
public:
    
    static FightResult * dealWithFight(BattleField * field, Creature * subject, Creature * target);
    
    static MagicResult * dealWithMagic(BattleField * field, Creature * subject, Vector<Creature * > targets, int magicId);
    
    
};

#endif /* GameFormula_hpp */
