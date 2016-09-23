//
//  ShopDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "ShopDefinition.hpp"


ShopDefinition * ShopDefinition::readFromFile(TextFileReader *reader)
{
    ShopDefinition * definition = new ShopDefinition(reader);
    definition->autorelease();
    return definition;
}

ShopDefinition::ShopDefinition(TextFileReader * reader)
{
    int count = reader->readInt();
    
    for (int i = 0; i < count; i++) {
        int item = reader->readInt();
        _itemList.pushBack(FDNumber::numberWithInt(item));
    }
}


Vector<FDNumber *> ShopDefinition::itemList()
{
    return _itemList;
}