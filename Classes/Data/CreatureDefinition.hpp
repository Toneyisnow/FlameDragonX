//
//  CreatureDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef CreatureDefinition_hpp
#define CreatureDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FDNumber.hpp"

USING_NS_CC;

class CreatureDefinition : public Ref
{
private:
    
    
public:
    
    static CreatureDefinition * readFromFile(TextFileReader * reader);
    static CreatureDefinition * readBaseInfoFromFile(TextFileReader * reader);
    static CreatureDefinition * readFromFile(TextFileReader * reader, Map<int, CreatureDefinition *> * dict);

    CreatureDefinition();
    
    std::string name;
    int definitionId;
    int animationId;
    int race;
    int occupation;
    int initialLevel;
    int initialAP, initialDP, initialDX, initialMV, initialEX;
    int initialHP, initialMP;
    
    Vector<FDNumber *> * initialItemList;
    Vector<FDNumber *> * initialMagicList;
    
    
    bool canFly();
    bool isKnight();
    int getMaximumLevel();
    bool canEquip(int itemId);
    
};
#endif /* CreatureDefinition_hpp */
