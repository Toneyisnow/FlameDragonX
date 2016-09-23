//
//  OccupationDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "OccupationDefinition.hpp"

OccupationDefinition * OccupationDefinition::readFromFile(TextFileReader *reader)
{
    OccupationDefinition * definition = new OccupationDefinition(reader);
    definition->autorelease();
    return definition;
}

OccupationDefinition::OccupationDefinition(TextFileReader * reader)
{
    _occupationId = reader->readInt();
    
    int attackCount = reader->readInt();
    for (int i = 0 ; i < attackCount; i++) {
        int itemCategory = reader->readInt();
        _attackItemCategoryList.pushBack(FDNumber::numberWithInt(itemCategory));
    }
    int defendCount = reader->readInt();
    for (int i = 0 ; i < defendCount; i++) {
        int itemCategory = reader->readInt();
        _defendItemCategoryList.pushBack(FDNumber::numberWithInt(itemCategory));
    }
    
    _magicDefenseRate = reader->readInt();
}

int OccupationDefinition::occupationId()
{
    return _occupationId;
}

Vector<FDNumber *> OccupationDefinition::attackItemCategoryList()
{
    return _attackItemCategoryList;
}

Vector<FDNumber *> OccupationDefinition::defendItemCategoryList()
{
    return _defendItemCategoryList;
}

int OccupationDefinition::magicDefenseRate()
{
    return _magicDefenseRate;
}

bool OccupationDefinition::canUseAttackItem(int attackItemCategory)
{
    for (FDNumber * itemCategory : _attackItemCategoryList) {
        if (itemCategory->getValue() == attackItemCategory)
            return true;
    }
    return false;
}

bool OccupationDefinition::canUseDefendItem(int defendItemCategory)
{
    for (FDNumber * itemCategory : _defendItemCategoryList) {
        if (itemCategory->getValue() == defendItemCategory)
            return true;
    }
    return false;
}
