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

USING_NS_CC;

class DataStore : public Ref
{
private:
    
    static DataStore * _instance;
    
    Map<int, CreatureDefinition *> * _creatureDefinitionDictionary;
    Map<int, ItemDefinition *> * _itemDefinitionDictionary;
    Map<int, MagicDefinition *> * _magicDefinitionDictionary;
    
    
    
public:
    
    DataStore();
    ~DataStore();
    
    static DataStore * getInstance();
    
    void loadData();
    void loadCreatureDefinition();
    void loadItemDefinition();
    void loadMagicDefinition();
    
    CreatureDefinition * getCreatureDefinition(int creatureId);
    ItemDefinition * getItemDefinition(int itemId);
    MagicDefinition * getMagicDefinition(int magicId);
};
#endif /* DataStore_hpp */
