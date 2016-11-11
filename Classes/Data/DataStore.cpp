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
    
    this->_levelUpDefinitionDictionary->clear();
    delete this->_levelUpDefinitionDictionary;
    
    this->_levelUpMagicDefinitionDictionary->clear();
    delete this->_levelUpMagicDefinitionDictionary;
    
    this->_shopDefinitionDictionary->clear();
    delete this->_shopDefinitionDictionary;
    
    this->_occupationDefinitionDictionary->clear();
    delete this->_occupationDefinitionDictionary;
    
    this->_transfersDefinitionDictionary->clear();
    delete this->_transfersDefinitionDictionary;
    
    this->_fightAnimationDefinitionDictionary->clear();
    delete this->_fightAnimationDefinitionDictionary;
}

void DataStore::loadData()
{
    this->loadCreatureDefinition();
    this->loadItemDefinition();
    this->loadMagicDefinition();
    this->loadLevelUpDefinition();
    this->loadLevelUpMagicDefinition();
    this->loadShopDefinition();
    this->loadOccupationDefinition();
    this->loadTransfersDefinition();
    this->loadFightAnimationDefinition();
    
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

void DataStore::loadLevelUpDefinition()
{
    log("Loading Level Up Definition");
    
    _levelUpDefinitionDictionary = new Map<int, LevelUpDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Levelup.dat");
    
    int count = reader->readInt();
    for (int m = 0; m < count; m++) {
        LevelUpDefinition * def = LevelUpDefinition::readFromFile(reader);
        _levelUpDefinitionDictionary->insert(def->definitionId(), def);
    }
    
    reader->release();
    
    log("Loaded Level Up Definition");
}

void DataStore::loadLevelUpMagicDefinition()
{
    log("Loading Level Up Magic Definition");
    
    _levelUpMagicDefinitionDictionary = new Map<int, LevelUpMagicDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/LevelupMagic.dat");
    
    LevelUpMagicDefinition * def = LevelUpMagicDefinition::readFromFile(reader);
    
    while (def != nullptr)
    {
        int key = generateLevelUpMagicKey(def->definitionId(), def->creatureLevel());
        _levelUpMagicDefinitionDictionary->insert(key, def);
        def = LevelUpMagicDefinition::readFromFile(reader);
    }
    
    reader->release();
    
    log("Loaded Level Up Magic Definition");
}


void DataStore::loadShopDefinition()
{
    log("Loading Shop Definition");
    
    _shopDefinitionDictionary = new Map<int, ShopDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Shop.dat");
    
    int chapter;
    while ((chapter = reader->readInt()) > 0) {
        int type = reader->readInt();
        int key = chapter * 10 + type;
        ShopDefinition * shop = ShopDefinition::readFromFile(reader);
        _shopDefinitionDictionary->insert(key, shop);
    }
    
    reader->release();
    log("Loaded Shop Definition");
}

void DataStore::loadOccupationDefinition()
{
    log("Loading Occupation Definition");
    
    _occupationDefinitionDictionary = new Map<int, OccupationDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Occupation.dat");
    
    int count = reader->readInt();
    for (int i = 0; i < count; i++) {
        OccupationDefinition * def = OccupationDefinition::readFromFile(reader);
        _occupationDefinitionDictionary->insert(def->occupationId(), def);
    }
    
    reader->release();
    log("Loaded Occupation Definition");
}

void DataStore::loadTransfersDefinition()
{
    log("Loading Transfers Definition");
    
    _transfersDefinitionDictionary = new Map<int, TransfersDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/Transfer.dat");
    
    int count = reader->readInt();
    for (int i = 0; i < count; i++) {
        TransfersDefinition * def = TransfersDefinition::readFromFile(reader);
        _transfersDefinitionDictionary->insert(def->creatureDefId(), def);
    }
    
    reader->release();
    log("Loaded Transfers Definition");
}

void DataStore::loadFightAnimationDefinition()
{
    log("Loading the FightAnimation Definition.");
    
    _fightAnimationDefinitionDictionary = new Map<int, FightAnimationDefinition *>();
    TextFileReader * reader = new TextFileReader("Data/FightAnimation.dat");
    
    int animationId = reader->readInt();
    while (animationId > 0) {
        int animationCount = reader->readInt();
        
        // Idle Animation
        FightAnimationDefinition * idleAnimation = new FightAnimationDefinition(animationId, FightAnimationType_Idle);
        idleAnimation->readFromFile(reader);
        _fightAnimationDefinitionDictionary->insert(animationId * 10 + FightAnimationType_Idle, idleAnimation);
        idleAnimation->release();
        
        // Attack Animation
        FightAnimationDefinition * attackAnimation = new FightAnimationDefinition(animationId, FightAnimationType_Attack);
        attackAnimation->readFromFile(reader);
        _fightAnimationDefinitionDictionary->insert(animationId * 10 + FightAnimationType_Attack, attackAnimation);
        attackAnimation->release();
        
        // Skil Animation
        if (animationCount > 2) {
            FightAnimationDefinition * skillAnimation = new FightAnimationDefinition(animationId, FightAnimationType_Skill);
            skillAnimation->readFromFile(reader);
            _fightAnimationDefinitionDictionary->insert(animationId * 10 + FightAnimationType_Skill, skillAnimation);
            skillAnimation->release();
        }
        else {
            _fightAnimationDefinitionDictionary->insert(animationId * 10 + FightAnimationType_Skill, attackAnimation);
        }
        
        animationId = reader->readInt();
    }
    
    reader->release();
    log("Loaded the FightAnimation Definition.");
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

LevelUpDefinition * DataStore::getLevelUpDefinition(int definitionId)
{
    return this->_levelUpDefinitionDictionary->at(definitionId);
}

LevelUpMagicDefinition * DataStore::getLevelUpMagicDefinition(int creatureId, int creatureLevel)
{
    return this->_levelUpMagicDefinitionDictionary->at(generateLevelUpMagicKey(creatureId, creatureLevel));
}

ShopDefinition * DataStore::getShopDefinition(int chapterId, ShopType shopType)
{
    return this->_shopDefinitionDictionary->at(generateShopKey(chapterId, shopType));
}

OccupationDefinition * DataStore::getOccupationDefinition(int occupationId)
{
    return this->_occupationDefinitionDictionary->at(occupationId);
}

TransfersDefinition * DataStore::getTransfersDefinition(int creatureId)
{
    return this->_transfersDefinitionDictionary->at(creatureId);
}

TransferDefinition * DataStore::getTransferDefinition(int transferId)
{
    int creatureDefId = transferId % 100;
    TransfersDefinition * transfers = getTransfersDefinition(creatureDefId);
    
    for (int i = 0; i < transfers->totalCount(); i++) {
        TransferDefinition * transfer = transfers->getTransfer(i);
        if (transfer->transferId() == transferId) {
            return transfer;
        }
    }
    
    return nullptr;
}

FightAnimationDefinition * DataStore::getFightAnimationDefinition(int animationId, FightAnimationType type)
{
    return this->_fightAnimationDefinitionDictionary->at(animationId * 10 + type);
}

int DataStore::generateShopKey(int chapterId, ShopType shopType)
{
    return chapterId * 10 + shopType;
}

int DataStore::generateLevelUpMagicKey(int creatureId, int creatureLevel)
{
    return creatureId * 100 + creatureLevel;
}

int DataStore::getMaxFriendCount(int chapterId)
{
    return (chapterId <= 26) ? 16 : 20;
}

