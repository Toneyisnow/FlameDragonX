//
//  MagicDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef MagicDefinition_hpp
#define MagicDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FDRange.hpp"

USING_NS_CC;

typedef enum MagicType
{
    MagicType_Attack = 1,
    MagicType_Recover = 2,
    MagicType_Offensive = 3,
    MagicType_Defensive = 4
    
} MagicType;

class Creature;

class MagicDefinition : public cocos2d::Ref
{
private:
    
    int _definitionId;
    
    std::string _name;
    
    MagicType _type;
    FDRange * _quantityRange;
    
    int _apInvolvedRate;
    int _hittingRate;
    int _effectScope;
    int _effectCoverage;
    int _mpCost;
    bool _allowAfterMove;
    int _aiConsiderRate;
    
public:
    
    static MagicDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
    int effectScope();
    int effectCoverage();
    int hittingRate();
    int mpCost();
    bool allowAfterMove();
    int aiConsiderRate();
    int apInvolvedRate();
    
    FDRange * getEffectScope();
    FDRange * getQuantityRange();
    
    int getDefinitionId();
    MagicType getType();
    
    bool hasAnimation();
    bool isCross();
    
    void takeOffensiveEffect(Creature * target);
    void takeDeffensiveEffect(Creature * target);
    
    int baseExperience();
};

#endif /* MagicDefinition_hpp */
