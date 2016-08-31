//
//  CreatureData.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#include "CreatureData.hpp"

CreatureData::CreatureData()
{
    hpCurrent = 0;
    hpMax = 0;
    mpCurrent = 0;
    mpMax = 0;
    
    
    attackItemIndex = -1;
    defenseItemIndex = -1;
    
    statusEnhanceAp = 0;
    statusEnhanceDp = 0;
    statusEnhanceDx = 0;
    statusPoisoned = 0;
    statusFrozen = 0;
    statusProhibited = 0;
    
    itemList = new Vector<FDNumber *>();
    magicList = new Vector<FDNumber *>();
    
    
}

CreatureData::~CreatureData()
{
    itemList->clear();
    magicList->clear();
    
}