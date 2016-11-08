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

int CreatureData::calculatedAp()
{
    int deltaAp = 0;
    AttackItemDefinition * item = this->getAttackItem();
    if (item != nullptr)
    {
        deltaAp = item->ap();
    }
    
    int total = ap + deltaAp;
    if (statusEnhanceAp > 0) {
        total += 0.15 * total;
    }
    
    return total;
    
}
int CreatureData::calculatedDp()
{
    int deltaDp = 0;
    AttackItemDefinition * item = this->getAttackItem();
    if (item != nullptr)
    {
        deltaDp = item->dp();
    }
    DefendItemDefinition * itemD = this->getDefendItem();
    if (itemD != nullptr)
    {
        deltaDp += itemD->dp();
    }
    
    int total = dp + deltaDp;
    if (statusEnhanceDp > 0) {
        total += 0.15 * total;
    }
    
    return total;
}

int CreatureData::calculatedHit()
{
    int deltaHit = 0;
    AttackItemDefinition * item = this->getAttackItem();
    if (item != nullptr)
    {
        deltaHit = item->hit();
    }
    
    int total = dx + deltaHit;
    if (statusEnhanceDx) {
        total += 0.15 * total;
    }
    
    return total;
}

int CreatureData::calculatedEv()
{
    int deltaEv = 0;
    AttackItemDefinition * item = this->getAttackItem();
    if (item != nullptr)
    {
        deltaEv += item->ev();
    }
    DefendItemDefinition * itemD = this->getDefendItem();
    if (itemD != nullptr)
    {
        deltaEv += itemD->ev();
    }
    
    int total = dx + deltaEv;
    if (statusEnhanceDx) {
        total += 0.15 * total;
    }
    
    return total;
}

int CreatureData::calculatedApWithItem(int itemId)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    if (item->isAttackItem()) {
        return ap + ((AttackItemDefinition *)item)->ap();
    }
    return calculatedAp();
}

int CreatureData::calculatedDpWithItem(int itemId)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    if (item->isAttackItem()) {
        
        return calculatedDp() + ((AttackItemDefinition *)item)->dp();
    }
    else if (item->isDefendItem())
    {
        return dp + ((DefendItemDefinition *)item)->dp();
    }
    
    return calculatedDp();
}
int CreatureData::calculatedHitWithItem(int itemId)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    if (item->isAttackItem()) {
        return hit + ((AttackItemDefinition *)item)->hit();
    }
    return calculatedHit();
}

int CreatureData::calculatedEvWithItem(int itemId)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    if (item->isAttackItem()) {
        
        return calculatedEv() + ((AttackItemDefinition *)item)->ev();
    }
    else if (item->isDefendItem())
    {
        return dx + ((DefendItemDefinition *)item)->ev();
    }
    
    return calculatedEv();
}

bool CreatureData::isItemFull()
{
    return (itemList->size() >= ITEM_MAX);
}

bool CreatureData::isItemEmpty()
{
    return itemList->size() == 0;
}

void CreatureData::removeItem(int itemIndex)
{
    if (itemIndex < 0 || itemIndex >= itemList->size()) {
        return;
    }
    
    if (attackItemIndex == itemIndex) {
        attackItemIndex = -1;
    }
    else if (attackItemIndex > itemIndex)
    {
        attackItemIndex --;
    }
    
    if (defendItemIndex == itemIndex) {
        defendItemIndex = -1;
    }
    else if (defendItemIndex > itemIndex)
    {
        defendItemIndex --;
    }
    
    itemList->erase(itemIndex);
}

void CreatureData::addItem(int itemId)
{
    if (itemList->size() >= ITEM_MAX) {
        return;
    }
    
    itemList->pushBack(FDNumber::numberWithInt(itemId));
}

void CreatureData::clearStatusPoisoned()
{
    statusPoisoned = 0;
}

void CreatureData::clearStatusFrozen()
{
    statusFrozen = 0;
}

void CreatureData::clearStatusProhibited()
{
    statusProhibited = 0;
}

