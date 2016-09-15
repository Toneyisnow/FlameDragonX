//
//  CreatureData.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#include "CreatureData.hpp"
#include "DataStore.hpp"

CreatureData::CreatureData()
{
    hpCurrent = 0;
    hpMax = 0;
    mpCurrent = 0;
    mpMax = 0;
    
    
    attackItemIndex = -1;
    defendItemIndex = -1;
    
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

AttackItemDefinition * CreatureData::getAttackItem()
{
    if (attackItemIndex < 0)
        return nullptr;
    
    int attackItemId = itemList->at(attackItemIndex)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(attackItemId);
    
    return (AttackItemDefinition *)item;
}

DefendItemDefinition * CreatureData::getDefendItem()
{
    if (defendItemIndex < 0)
        return nullptr;
    
    int defendItemId = itemList->at(defendItemIndex)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(defendItemId);
    
    return (DefendItemDefinition *)item;
}

ItemDefinition * CreatureData::getItem(int itemIndex)
{
    if (itemIndex < 0 || itemIndex >= itemList->size())
    {
        return nullptr;
    }
    
    int itemId = itemList->at(itemIndex)->getValue();
    return DataStore::getInstance()->getItemDefinition(itemId);
}

MagicDefinition * CreatureData::getMagic(int magicIndex)
{
    if (magicIndex < 0 || magicIndex >= magicList->size())
    {
        return nullptr;
    }
    
    int magicId = magicList->at(magicIndex)->getValue();
    return DataStore::getInstance()->getMagicDefinition(magicId);
}
