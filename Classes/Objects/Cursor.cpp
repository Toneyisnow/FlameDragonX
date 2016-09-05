//
//  Cursor.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/3/16.
//
//

#include "Cursor.hpp"
#include "StringUtil.hpp"

Cursor::Cursor()
: BattleObject(BattleObject_Cursor)
{
    _cursorSize = 1;
    initialize(StringUtil::format("Others/Cursor-%02d.png", _cursorSize));
    
}

void Cursor::setSize(int size)
{
    _cursorSize = size;
}