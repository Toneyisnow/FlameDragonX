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

USING_NS_CC;

class DataStore : public Ref
{
private:
    
    static DataStore * _instance;
    
    Map<int, CreatureDefinition *> * _creatureDefinitionDictionary;
    Map<int, ItemDefinition *> * _itemDefinitionDictionary;
    
    
    
public:
    
    DataStore();
    ~DataStore();
    
    static DataStore * getInstance();
    
    void loadData();
    void loadCreatureDefinition();
    void loadItemDefinition();
    
    
    CreatureDefinition * getCreatureDefinition(int creatureId);
    ItemDefinition * getItemDefinition(int itemId);
    
};
#endif /* DataStore_hpp */
