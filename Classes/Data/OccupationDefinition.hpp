//
//  OccupationDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef OccupationDefinition_hpp
#define OccupationDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FDNumber.hpp"

class OccupationDefinition : public cocos2d::Ref
{
private:
    
    int _occupationId;
    Vector<FDNumber *> _attackItemCategoryList;
    Vector<FDNumber *> _defendItemCategoryList;
    
    int _magicDefenseRate;
    
public:
    
    static OccupationDefinition * readFromFile(TextFileReader *reader);
    OccupationDefinition(TextFileReader * reader);
    
    int occupationId();
    Vector<FDNumber *> attackItemCategoryList();
    Vector<FDNumber *> defendItemCategoryList();
    
    int magicDefenseRate();
    
    bool canUseAttackItem(int attackItemCategory);
    bool canUseDefendItem(int defendItemCategory);
};

#endif /* OccupationDefinition_hpp */
