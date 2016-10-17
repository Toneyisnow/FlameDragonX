//
//  FDAction.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#include "FDAction.hpp"

FDAction::FDAction(Sprite * sprite)
{
    this->_sprite = sprite;
    
    this->_currentTick = 0;
    this->_hasFinished = false;
    
    _tag = 0;
}

FDAction::~FDAction()
{
}

void FDAction::reset()
{
    this->_currentTick = 0;
    this->_hasFinished = false;
}

void FDAction::takeTick(int synchronizedTick)
{
    // Should be implemented by subclass
}

bool FDAction::hasFinished()
{
    return _hasFinished;
}

void FDAction::setTag(int tag)
{
    _tag = tag;
}

int FDAction::getTag()
{
    return _tag;
}

int FDAction::getTotalTick()
{
    // Should be implemented by subclass
    return 0;
}
