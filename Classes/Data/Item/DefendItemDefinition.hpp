//
//  DefendItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#ifndef DefendItemDefinition_hpp
#define DefendItemDefinition_hpp


#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "ItemDefinition.hpp"

USING_NS_CC;

class DefendItemDefinition : public ItemDefinition
{
private:
    
    // For Defend Item: 1：皮甲 2：锁甲 3：铠甲 4：袍 5：斗服 6：装甲
    int _itemCategory;
    
    int _dp;
    int _ev;
    
    
public:
    
    static DefendItemDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
    int dp();
    int ev();
    int itemCategory();
    
};
#endif /* DefendItemDefinition_hpp */
