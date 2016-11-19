//
//  ItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef ItemDefinition_hpp
#define ItemDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"

USING_NS_CC;

typedef enum ItemType
{
    ItemType_Usable,
    ItemType_Equip,
    ItemType_MultiUsable,
    ItemType_NotUsable
} ItemType;

class ItemDefinition : public cocos2d::Ref
{
protected:
    
    int _definitionId;
    
    std::string _name;
    
    ItemType type;	// It's not used yet, just the class can differenciate them
    int _price;
    int _sellprice;
    
    int _category;	// For Attack Item: 1：剑 2：斧 3：矛 4：弓 5：爪 6：机械
                    // For Defend Item: 1：皮甲 2：锁甲 3：铠甲 4：袍 5：斗服 6：装甲
    
public:
    
    ItemDefinition();
    
    int getDefinitionId();
    
    std::string getName();
    
    std::string getAttributeString();
    
    int getPrice();
    int getSellPrice();
    
    bool isMoney();
    bool isAttackItem();
    bool isDefendItem();
    bool isUsableItem();
};

#endif /* ItemDefinition_hpp */
