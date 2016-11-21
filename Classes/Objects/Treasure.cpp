//
//  Treasure.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/20/16.
//
//

#include "Treasure.hpp"

using namespace std;

Treasure::Treasure(int itemId, int boxType)
: BattleObject(BattleObject_Treasure)
{
    _itemId = itemId;
    _boxType = boxType;
    _hasOpened = false;
    
    initialize("Others/Empty.png");
}

void Treasure::setOpened(bool value)
{
    _hasOpened = value;
}

int Treasure::itemId()
{
    return _itemId;
}

int Treasure::boxType()
{
    return _boxType;
}

bool Treasure::hasOpened()
{
    return _hasOpened;
}

void Treasure::changeItem(int itemId)
{
    _itemId = itemId;
}
