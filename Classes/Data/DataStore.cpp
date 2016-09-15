//
//  DataStore.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "DataStore.hpp"
#include "TextFileReader.hpp"
#include "Constants.hpp"
#include "StringUtil.hpp"
#include "UsableItemDefinition.hpp"
#include "AttackItemDefinition.hpp"
#include "DefendItemDefinition.hpp"
#include "SpecialItemDefinition.hpp"
#include "MoneyItemDefinition.hpp"
#include "MagicDefinition.hpp"

DataStore * DataStore::_instance = nullptr;

DataStore * DataStore::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new DataStore();
    }
    
    return _instance;
}

DataStore::DataStore()
{
    
}

DataStore::~DataStore()
{
    this->_creatureDefinitionDictionary->clear();
    delete this->_creatureDefinitionDictionary;
    
    this->_itemDefinitionDictionary->clear();
    delete this->_itemDefinitionDictionary;
    
    this->_magicDefinitionDictionary->clear();
    delete this->_magicDefinitionDictionary;
    
}

void DataStore::loadData()
{
    this->loadCreatureDefinition();
    this->loadItemDefinition();
    this->loadMagicDefinition();
    
}

void DataStore::loadCreatureDefinition()
{
    log("Loading Creature Definition.");
    this->_creatureDefinitionDictionary = new Map<int, CreatureDefinition *>();
    
    TextFileReader * reader = new TextFileReader("Data/Creature.dat");
    int creatureCount = reader->readInt();
    
    for (int i = 0; i < creatureCount; i++) {
        CreatureDefinition * definition = CreatureDefinition::readFromFile(reader);
        this->_creatureDefinitionDictionary->insert(definition->definitionId, definition);
    }
    
    reader->release();
    log("Loaded Creature Definition.");
    
    log("Loading Leveled Creature Definition.");
    reader = new TextFileReader("Data/LeveledCreature.dat");
    
    int baseInfoCount = reader->readInt();
    Map<int, CreatureDefinition *> * baseInfoDict = new Map<int, CreatureDefinition *>();
    for (int m = 0; m < baseInfoCount; m++)
    {
        CreatureDefinition *def = CreatureDefinition::readBaseInfoFromFile(reader);
        baseInfoDict->insert(def->definitionId, def);
    }
    
    reader->release();
    log("Loaded Leveled Creature Definition.");
    
    // Read enemy/NPC data
    for (int level = 1; level <= Constants::LEVEL_COUNT; level++) {
        
        TextFileReader * levelFile = new TextFileReader(StringUtil::format("Data/Maps/Chapter-%02d-Creature.dat", level));
        
        int leveledCreatureCount = levelFile->readInt();
        for (int m = 0; m < leveledCreatureCount; m++) {
            CreatureDefinition *definition = CreatureDefinition::readFromFile(levelFile, baseInfoDict);
            this->_creatureDefinitionDictionary->insert(definition->definitionId, definition);
        }
        
        levelFile->release();
    }
    
    baseInfoDict->clear();
    delete baseInfoDict;
    
    log("Loaded Leveled Creature Dictionary.");
    
}

void DataStore::loadItemDefinition()
{
    log("Loading Item Definition");
    
    _itemDefinitionDictionary = new Map<int, ItemDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Item.dat");
    
    int usableCount = reader->readInt();
    for (int m = 0; m < usableCount; m++) {
        UsableItemDefinition * def = UsableItemDefinition::readFromFile(reader);
        _itemDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    int attackCount = reader->readInt();
    for (int m = 0; m < attackCount; m++) {
        AttackItemDefinition * def = AttackItemDefinition::readFromFile(reader);
        _itemDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    int defendCount = reader->readInt();
    for (int m = 0; m < defendCount; m++) {
        DefendItemDefinition * def = DefendItemDefinition::readFromFile(reader);
        _itemDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    int specialCount = reader->readInt();
    for (int m = 0; m < specialCount; m++) {
        SpecialItemDefinition * def = SpecialItemDefinition::readFromFile(reader);
        _itemDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    int moneyCount = reader->readInt();
    for (int m = 0; m < moneyCount; m++) {
        MoneyItemDefinition * def = MoneyItemDefinition::readFromFile(reader);
        _itemDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    reader->release();
    
    log("Loaded Item Definition");
    
}

void DataStore::loadMagicDefinition()
{
    log("Loading Magic Definition");
    
    _magicDefinitionDictionary = new Map<int, MagicDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Magic.dat");
    
    int magicCount = reader->readInt();
    for (int m = 0; m < magicCount; m++) {
        MagicDefinition * def = MagicDefinition::readFromFile(reader);
        _magicDefinitionDictionary->insert(def->getDefinitionId(), def);
    }
    
    reader->release();
    
    log("Loaded Magic Definition");
}

///////////////////////////////////////////


CreatureDefinition * DataStore::getCreatureDefinition(int definitionId)
{
    return this->_creatureDefinitionDictionary->at(definitionId);
}

ItemDefinition * DataStore::getItemDefinition(int itemId)
{
    return this->_itemDefinitionDictionary->at(itemId);
}

MagicDefinition * DataStore::getMagicDefinition(int magicId)
{
    return this->_magicDefinitionDictionary->at(magicId);
}
