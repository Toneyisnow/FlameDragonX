//
//  UsableItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef UsableItemDefinition_hpp
#define UsableItemDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "ItemDefinition.hpp"

USING_NS_CC;

typedef enum UsableItemType
{
    UsableItemType_Hp = 1,
    UsableItemType_Mp = 2,
    UsableItemType_AntiFreeze = 3,
    UsableItemType_AntiPoison = 4,
    UsableItemType_MaxHp = 5,
    UsableItemType_MaxMp = 6,
    UsableItemType_Ap = 7,
    UsableItemType_Dp = 8,
    UsableItemType_Mv = 9,
    UsableItemType_Dx = 10,
    UsableItemType_EyeStar = 11,
    UsableItemType_EyeDark = 12,
    UsableItemType_EyeIce = 13,
    UsableItemType_EyeFire = 14
    
    
} UsableItemType;


class UsableItemDefinition : public ItemDefinition
{
private:
    
    UsableItemType _useType;
    int _quantity;
    bool _isReusable;
    
public:
    
    static UsableItemDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
    bool isReusable();
    bool onlyUseToSelf();
    
};

#endif /* UsableItemDefinition_hpp */
