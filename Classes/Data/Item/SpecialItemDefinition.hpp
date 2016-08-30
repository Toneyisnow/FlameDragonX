//
//  SpecialItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef SpecialItemDefinition_hpp
#define SpecialItemDefinition_hpp
#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "ItemDefinition.hpp"

USING_NS_CC;

class SpecialItemDefinition : public ItemDefinition
{
private:
    
public:
    
    static SpecialItemDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
};


#endif /* SpecialItemDefinition_hpp */
