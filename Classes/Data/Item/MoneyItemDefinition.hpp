//
//  MoneyItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef MoneyItemDefinition_hpp
#define MoneyItemDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "ItemDefinition.hpp"

USING_NS_CC;

class MoneyItemDefinition : public ItemDefinition
{
private:
    
    int _quantity;
    
public:
    
    static MoneyItemDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
    int quantity();
};

#endif /* MoneyItemDefinition_hpp */
