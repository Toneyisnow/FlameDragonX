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
#include "MagicDefinition.hpp"
#include "FDNumber.hpp"

class CreatureData : public cocos2d::Ref
{
private:
    
    
public:
    
    static const int ITEM_MAX = 8;
    static const int MAGIC_MAX = 12;
    
    
    int hpCurrent, hpMax, mpCurrent, mpMax;
    int level, ap, dp, hit, dx, mv, ex;
    
    int attackItemIndex;
    int defendItemIndex;
    
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
    
    int calculatedAp();
    int calculatedDp();
    int calculatedHit();
    int calculatedEv();
    
    
    
    
    AttackItemDefinition * getAttackItem();
    DefendItemDefinition * getDefendItem();
    ItemDefinition * getItem(int itemIndex);
    MagicDefinition * getMagic(int magicIndex);
    
    bool isItemFull();
    void removeItem(int itemIndex);
    void addItem(int itemId);
    
};

#endif /* CreatureData_hpp */
