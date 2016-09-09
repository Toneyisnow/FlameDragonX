//
//  StateSession.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "StateSession.hpp"
#include "MoveScopeResolver.hpp"

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
    _scopeResolver = nullptr;
    
    creaturePositionAfterMove = Vec2(0, 0);
    creaturePositionBeforeMove = Vec2(0, 0);
    menuPosition = Vec2(0, 0);
}

StateSession::~StateSession()
{
    if (_scopeResolver != nullptr)
    {
        _scopeResolver->release();
    }
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

void StateSession::setMoveScopeResolver(MoveScopeResolver * resolver)
{
    _scopeResolver = resolver;
    _scopeResolver->retain();
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

MoveScopeResolver * StateSession::getMoveScopeResolver()
{
    return _scopeResolver;
}