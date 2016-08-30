//
//  SpecialItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "SpecialItemDefinition.hpp"

SpecialItemDefinition * SpecialItemDefinition::readFromFile(TextFileReader * reader)
{
    SpecialItemDefinition * def = new SpecialItemDefinition();
    
    def->initFromFile(reader);
    def->autorelease();
    return def;
}

void SpecialItemDefinition::initFromFile(TextFileReader * reader)
{
    _definitionId = reader->readInt();
    
    _price = reader->readInt();
    _sellprice = reader->readInt();
}

