//
//  CursorMoveActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "CursorMoveActivity.hpp"
#include "Constants.hpp"
#include "BattleField.hpp"

CursorMoveActivity * CursorMoveActivity::create(BattleField * field, Cursor * cursor, Vec2 toPoint)
{
    CursorMoveActivity * activity = new CursorMoveActivity(field, cursor);
    
    Point currentPosition = field->getObjectPosition(cursor);
    if (currentPosition.x == toPoint.x || currentPosition.y == toPoint.y)
    {
        activity->appendPosition(toPoint.x, toPoint.y);
    }
    else
    {
        // Random choose one
        if (rand() % 2 == 1)
        {
            activity->appendPosition(toPoint.x, currentPosition.y);
        }
        else
        {
            activity->appendPosition(currentPosition.x, toPoint.y);
        }
        
        activity->appendPosition(toPoint.x, toPoint.y);
        
    }
    
    activity->autorelease();
    return activity;
}

CursorMoveActivity::CursorMoveActivity(BattleField * field, Cursor * cursor)
{
    this->_field = field;
    this->_cursor = cursor;
}

void CursorMoveActivity::appendPosition(int posX, int posY)
{
    SimpleMoveActivity * activity = new SimpleMoveActivity(_field, _cursor, Vec2(posX, posY), Constants::CURSOR_MOVE_SPEED);
    this->appendActivity(activity);
    activity->release();
}
