//
//  CursorMoveActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef CursorMoveActivity_hpp
#define CursorMoveActivity_hpp

#include "cocos2d.h"
#include "CombinedActivity.hpp"
#include "SimpleMoveActivity.hpp"
#include "Cursor.hpp"

class BattleField;

USING_NS_CC;

class CursorMoveActivity : public CombinedActivity
{
private:
    
    BattleField * _field;
    Cursor * _cursor;
    
public:
    
    static CursorMoveActivity * create(BattleField * field, Cursor * cursor, Vec2 toPoint);
    
    CursorMoveActivity(BattleField * field, Cursor * cursor);
    
    void appendPosition(int posX, int posY);
    
};

#endif /* CursorMoveActivity_hpp */
