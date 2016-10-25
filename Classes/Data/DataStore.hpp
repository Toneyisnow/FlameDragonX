//
//  DataStore.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef DataStore_hpp
#define DataStore_hpp


#include "cocos2d.h"
#include "CreatureDefinition.hpp"
#include "ItemDefinition.hpp"
#include "FDNumber.hpp"
#include "MagicDefinition.hpp"
#include "LevelUpDefinition.hpp"
#include "LevelUpMagicDefinition.hpp"
#include "ShopDefinition.hpp"
#include "OccupationDefinition.hpp"
#include "TransfersDefinition.hpp"
#include "FightAnimationDefinition.hpp"

USING_NS_CC;

class DataStore : public Ref
{
private:
    
    static DataStore * _instance;
    
    Map<int, CreatureDefinition *> * _creatureDefinitionDictionary;
    Map<int, ItemDefinition *> * _itemDefinitionDictionary;
    Map<int, MagicDefinition *> * _magicDefinitionDictionary;
    Map<int, LevelUpDefinition *> * _levelUpDefinitionDictionary;
    Map<int, LevelUpMagicDefinition *> * _levelUpMagicDefinitionDictionary;
    Map<int, ShopDefinition *> * _shopDefinitionDictionary;
    Map<int, OccupationDefinition *> * _occupationDefinitionDictionary;
    Map<int, TransfersDefinition *> * _transfersDefinitionDictionary;
    Map<int, FightAnimationDefinition *> * _fightAnimationDefinitionDictionary;
    
    static int generateShopKey(int chapterId, ShopType shopType);
    static int generateLevelUpMagicKey(int creatureId, int creatureLevel);
    
public:
    
    DataStore();
    ~DataStore();
    
    static DataStore * getInstance();
    
    void loadData();
    void loadCreatureDefinition();
    void loadItemDefinition();
    void loadMagicDefinition();
    void loadLevelUpDefinition();
    void loadLevelUpMagicDefinition();
    void loadShopDefinition();
    void loadOccupationDefinition();
    void loadTransfersDefinition();
    void loadFightAnimationDefinition();
    
    CreatureDefinition * getCreatureDefinition(int creatureId);
    ItemDefinition * getItemDefinition(int itemId);
    MagicDefinition * getMagicDefinition(int magicId);
    LevelUpDefinition * getLevelUpDefinition(int definitionId);
    LevelUpMagicDefinition * getLevelUpMagicDefinition(int creatureId, int creatureLevel);
    ShopDefinition * getShopDefinition(int chapterId, ShopType shopType);
    OccupationDefinition * getOccupationDefinition(int occupationId);
    TransfersDefinition * getTransfersDefinition(int creatureId);
    FightAnimationDefinition * getFightAnimationDefinition(int animationid, FightAnimationType type);
    int getMaxFriendCount(int chapterId);
    
};
#endif /* DataStore_hpp */
