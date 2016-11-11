//
//  CreatureDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "CreatureDefinition.hpp"
#include "LocalizedStrings.hpp"
#include "DataStore.hpp"
#include "AttackItemDefinition.hpp"
#include "DefendItemDefinition.hpp"

CreatureDefinition * CreatureDefinition::readFromFile(TextFileReader * reader)
{
    CreatureDefinition * def = new CreatureDefinition();
    
    def->definitionId = reader->readInt();
    def->animationId = def->definitionId % 1000;
    
    def->name = LocalizedStrings::getInstance()->getCreatureName(def->animationId);
    
    def->race = reader->readInt();
    def->occupation = reader->readInt();
    def->initialLevel = reader->readInt();
    def->initialAP = reader->readInt();
    def->initialDP = reader->readInt();
    def->initialDX = reader->readInt();
    def->initialHP= reader->readInt();
    def->initialMP = reader->readInt();
    def->initialMV = reader->readInt();
    def->initialEX = reader->readInt();
    
    // Read items
    def->initialItemList = new Vector<FDNumber *>();
    int itemCount = reader->readInt();
    for (int i = 0; i < itemCount; i ++) {
        int itemId = reader->readInt();
        def->initialItemList->pushBack(FDNumber::numberWithInt(itemId));
    }
    
    // Read magics
    def->initialMagicList = new Vector<FDNumber *>();
    int magicCount = reader->readInt();
    for (int i = 0; i < magicCount; i ++) {
         int magicId = reader->readInt();
        def->initialMagicList->pushBack(FDNumber::numberWithInt(magicId));
    }
    
    def->autorelease();
    return def;
}

CreatureDefinition * CreatureDefinition::readBaseInfoFromFile(TextFileReader * reader)
{
    CreatureDefinition * def = new CreatureDefinition();
    
    def->definitionId = reader->readInt();
    def->animationId = def->definitionId % 1000;
    
    def->name = LocalizedStrings::getInstance()->getCreatureName(def->animationId);
    
    def->race = reader->readInt();
    def->occupation = reader->readInt();
    def->initialAP = reader->readInt();
    def->initialDP = reader->readInt();
    def->initialDX = reader->readInt();
    def->initialHP= reader->readInt();
    def->initialMP = reader->readInt();
    def->initialMV = reader->readInt();
    def->initialEX = reader->readInt();
    
    def->autorelease();
    
    return def;
}
CreatureDefinition * CreatureDefinition::readFromFile(TextFileReader * reader, Map<int, CreatureDefinition *> * dict)
{
    if (dict == nullptr)
    {
        return nullptr;
    }
    
    CreatureDefinition * def = new CreatureDefinition();
    
    def->definitionId = reader->readInt();
    int baseId = reader->readInt();
    def->initialLevel = reader->readInt();
    
    CreatureDefinition * baseDef = dict->at(baseId);
    if (baseDef == nullptr)
    {
        log("Error Reading Creature Definition from leveled definition. definitionId=%d", def->definitionId);
        def->release();
        return nullptr;
    }
    
    def->animationId = baseDef->animationId;
    def->name = baseDef->name;
    
    def->race = baseDef->race;
    def->occupation = baseDef->occupation;
    def->initialAP = baseDef->initialAP * def->initialLevel;
    def->initialDP = baseDef->initialDP * def->initialLevel;
    def->initialDX = baseDef->initialDX * def->initialLevel;
    def->initialHP = baseDef->initialHP * def->initialLevel;
    def->initialMP = baseDef->initialMP * def->initialLevel;
    def->initialMV = baseDef->initialMV;
    def->initialEX = baseDef->initialEX;
    
    // Read items
    def->initialItemList = new Vector<FDNumber *>();
    int itemCount = reader->readInt();
    for (int i = 0; i < itemCount; i ++) {
        int itemId = reader->readInt();
        def->initialItemList->pushBack(FDNumber::numberWithInt(itemId));
    }
    
    // Read magics
    def->initialMagicList = new Vector<FDNumber *>();
    int magicCount = reader->readInt();
    for (int i = 0; i < magicCount; i ++) {
        int magicId = reader->readInt();
        def->initialMagicList->pushBack(FDNumber::numberWithInt(magicId));
    }
    
    def->autorelease();
    return def;
}

CreatureDefinition::CreatureDefinition()
{
    
}

bool CreatureDefinition::canFly()
{
    if (occupation == 133 || occupation == 171) {
        return true;
    }
        
    if (race == 6 && definitionId != 24) {
        return true;
    }
        
    if (race == 5) {
        return true;
    }
        
    if (race == 9 && occupation == 999) {
        return true;
    }
        
    return false;
}

bool CreatureDefinition::isKnight()
{
    return (occupation == 131 || occupation == 132);
}

int CreatureDefinition::getMaximumLevel()
{
    if (race == 7) {
        return 99;
    }
    
    return 40;
}

std::string CreatureDefinition::getOccupationName()
{
    return LocalizedStrings::getInstance()->getOccupationName(occupation);
}

bool CreatureDefinition::canEquip(int itemId)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    
    OccupationDefinition * occu = DataStore::getInstance()->getOccupationDefinition(occupation);
    
    return (item->isAttackItem() && occu->canUseAttackItem(((AttackItemDefinition *)item)->itemCategory()))
            || (item->isDefendItem() && occu->canUseDefendItem(((DefendItemDefinition *)item)->itemCategory()));
}
