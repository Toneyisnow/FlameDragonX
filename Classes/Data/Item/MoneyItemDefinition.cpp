//
//  MoneyItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "MoneyItemDefinition.hpp"
#include "LocalizedStrings.hpp"

MoneyItemDefinition * MoneyItemDefinition::readFromFile(TextFileReader * reader)
{
    MoneyItemDefinition * def = new MoneyItemDefinition();
    
    def->initFromFile(reader);
    def->autorelease();
    return def;
}

void MoneyItemDefinition::initFromFile(TextFileReader * reader)
{
    _definitionId = reader->readInt();
    
    _name = LocalizedStrings::getInstance()->getItemName(_definitionId);
    
    _quantity = reader->readInt();
    
}

int MoneyItemDefinition::quantity()
{
    return _quantity;
}
