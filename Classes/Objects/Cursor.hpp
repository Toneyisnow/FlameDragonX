//
//  Cursor.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/3/16.
//
//

#ifndef Cursor_hpp
#define Cursor_hpp

#include "cocos2d.h"
#include "BattleObject.hpp"


class Cursor : public BattleObject
{
private:
    
    int _cursorSize;
    
public:
    
    Cursor();
    
    void setSize(int size);
    
    
};

#endif /* Cursor_hpp */
