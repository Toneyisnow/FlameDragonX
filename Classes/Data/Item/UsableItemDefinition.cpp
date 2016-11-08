//
//  UsableItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "UsableItemDefinition.hpp"
#include "LocalizedStrings.hpp"

UsableItemDefinition * UsableItemDefinition::readFromFile(TextFileReader * reader)
{
    UsableItemDefinition * definition = new UsableItemDefinition();
    
    definition->initFromFile(reader);
    definition->autorelease();
    
    return definition;
}

void UsableItemDefinition::initFromFile(TextFileReader * reader)
{
    this->_definitionId = reader->readInt();
    
    /// this->name
    this->_name = LocalizedStrings::getInstance()->getItemName(_definitionId);
    
    this->_price = reader->readInt();
    this->_sellprice = reader->readInt();
    
    this->_useType = (UsableItemType)reader->readInt();
    this->_quantity = reader->readInt();
    
    this->_isReusable = (reader->readInt() == 1);
}

bool UsableItemDefinition::isReusable()
{
    return this->_isReusable;
}

bool UsableItemDefinition::onlyUseToSelf()
{
    return this->_definitionId >= 111 && this->_definitionId <= 115;
}

