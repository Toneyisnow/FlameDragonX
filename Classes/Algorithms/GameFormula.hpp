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
#include "CounterResult.hpp"
#include "MagicDefinition.hpp"

class BattleField;

class GameFormula : public cocos2d::Ref
{
    
private:
    
public:
    
    static FightResult * dealWithFight(BattleField * field, Creature * subject, Creature * target);
    
    static MagicResult * dealWithMagic(BattleField * field, Creature * subject, Vector<Creature * > &targets, int magicId);
    
    static CounterResult * singleAttack(BattleField * field, Creature * subject, Creature * target);
    static CounterResult * singleMagic(BattleField * field, Creature * subject, Creature * target, MagicDefinition * magic);
    
    static int calculateExperience(Creature * subject, Creature * target, CounterResult * counterResult);
    static int calculateMagicExperience(Creature * subject, Creature * target, MagicDefinition * magic);
    
    
    static int commonDoubleAttackRate();
    static int commonCriticalAttackRate();
    
    static int getCalculatedLevel(Creature * creature);
    
    static void actionedByEnhanceAp(Creature * target);
    static void actionedByEnhanceDp(Creature * target);
    static void actionedByEnhanceDx(Creature * target);
    static void actionedByPoision(Creature * target);
    static void actionedByProhibited(Creature * target);
    static void actionedByFrozen(Creature * target);
    
    
    
};

#endif /* GameFormula_hpp */
