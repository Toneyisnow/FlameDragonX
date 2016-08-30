//
//  AttackItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "AttackItemDefinition.hpp"

AttackItemDefinition * AttackItemDefinition::readFromFile(TextFileReader * reader)
{
    AttackItemDefinition * def = new AttackItemDefinition();
    
    def->initFromFile(reader);
    def->autorelease();
    return def;
}

AttackItemDefinition::~AttackItemDefinition()
{
    _attackRange->release();
}

void AttackItemDefinition::initFromFile(TextFileReader * reader)
{
    _definitionId = reader->readInt();
    
    /////_name = ;
    
    _itemCategory = reader->readInt();
    _price = reader->readInt();
    _sellprice = reader->readInt();
    
    _ap = reader->readInt();
    _dp = reader->readInt();
    _hit = reader->readInt();
    
    int scope = reader->readInt();
    if (scope > 2)
    {
        // Long Distance Amor
        _attackRange = FDRange::rangeWithValues(2, scope);
    }
    else
    {
        // Short Distance Amor
        _attackRange = FDRange::rangeWithValues(MIN(1, scope), scope);
    }
    _attackRange->retain();
    
    _ev = 0;
}

