//
//  CombinedAction.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#include "CombinedAction.hpp"

CombinedAction::CombinedAction(Sprite * sprite)
: FDAction(sprite)
{
    _actionList.clear();
    _currentAction = 0;
}

CombinedAction::~CombinedAction()
{
    _actionList.clear();
}

void CombinedAction::reset()
{
    for (FDAction * action : _actionList) {
        action->reset();
    }
    
    _currentAction = 0;
}

void CombinedAction::appendAction(FDAction * action)
{
    _actionList.pushBack(action);
}

void CombinedAction::takeTick(int synchronizedTick)
{
    if (_currentAction == _actionList.size()) {
        _hasFinished = true;
        return;
    }
    
    FDAction * action = _actionList.at(_currentAction);
    action->takeTick(synchronizedTick);
    
    if (action->hasFinished()) {
        _currentAction++;
    }
}

int CombinedAction::getTotalTick()
{
    int totalTick = 0;
    for (FDAction * action : _actionList)
    {
        totalTick += action->getTotalTick();
    }
    
    return totalTick;
}

FDAction * CombinedAction::getCurrentAction()
{
    return (_actionList.size() <= _currentAction) ? nullptr : _actionList.at(_currentAction);
}

int CombinedAction::getCurrentIndex()
{
    return _currentAction;
}

bool CombinedAction::hasFinished()
{
    return _hasFinished;
}
