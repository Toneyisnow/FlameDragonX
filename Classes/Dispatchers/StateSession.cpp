//
//  StateSession.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "StateSession.hpp"

StateSession * StateSession::newSession()
{
    StateSession * sess = new StateSession();
    
    sess->autorelease();
    return sess;
}
StateSession::StateSession()
{
    _selectedCreatureId = -1;
    _selectedItemIndex = -1;
    _selectedMagicIndex = -1;
    _lastPosition = Vec2(0, 0);
}

void StateSession::setSelectedCreatureId(int val)
{
    _selectedCreatureId = val;
}

void StateSession::setSelectedItemIndex(int val)
{
    _selectedItemIndex = val;
}

void StateSession::setSelectedMagicIndex(int val)
{
    _selectedMagicIndex = val;
}

void StateSession::setLastPosition(Vec2 position)
{
    _lastPosition = position;
}

int StateSession::selectedCreatureId()
{
    return _selectedCreatureId;
}

int StateSession::selectedItemIndex()
{
    return _selectedItemIndex;
}

int StateSession::selectedMagicIndex()
{
    return _selectedMagicIndex;
}

Vec2 StateSession::lastPosition()
{
    return _lastPosition;
}
