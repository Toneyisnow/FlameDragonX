//
//  ItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "ItemDefinition.hpp"

ItemDefinition::ItemDefinition()
{
    
}

int ItemDefinition::getDefinitionId()
{
    return _definitionId;
}

std::string ItemDefinition::getName()
{
    return _name;
}

int ItemDefinition::getPrice()
{
    return _price;
}
int ItemDefinition::getSellPrice()
{
    return _sellprice;
}

bool ItemDefinition::isMoney()
{
    return (_definitionId / 100 == 9);
}
bool ItemDefinition::isAttackItem()
{
    return (_definitionId / 100 == 2);
}
bool ItemDefinition::isDefendItem()
{
    return (_definitionId / 100 == 3);
}
