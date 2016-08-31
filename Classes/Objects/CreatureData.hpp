//
//  CreatureData.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#ifndef CreatureData_hpp
#define CreatureData_hpp

#include "cocos2d.h"
#include "AttackItemDefinition.hpp"
#include "DefendItemDefinition.hpp"
#include "FDNumber.hpp"

class CreatureData : public cocos2d::Ref
{
private:
    
    
public:
    
    static const int ITEM_MAX = 8;
    static const int MAGIC_MAX = 12;
    
    
    int hpCurrent, hpMax, mpCurrent, mpMax;
    int level, ap, dp, dx, mv, ex;
    
    int attackItemIndex;
    int defenseItemIndex;
    
    int statusEnhanceAp;
    int statusEnhanceDp;
    int statusEnhanceDx;
    int statusPoisoned;
    int statusFrozen;
    int statusProhibited;

    Vector<FDNumber *> * itemList;
    Vector<FDNumber *> * magicList;
    
    CreatureData();
    ~CreatureData();
    
    
    AttackItemDefinition * getAttackItem();
    DefendItemDefinition * getDefenseItem();
    
};

#endif /* CreatureData_hpp */
