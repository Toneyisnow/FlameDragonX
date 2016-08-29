//
//  FDActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "FDActivity.hpp"
#include "BattleScene.hpp"

FDActivity::FDActivity()
{
    this->_hasFinished = false;
    this->_isInitialized = false;
    
}

void FDActivity::internalTick(int synchronizedTick)
{
    
}

void FDActivity::takeTick(int synchronizedTick)
{
    if (!_isInitialized)
    {
        this->initialize();
        _isInitialized = true;
        return;
    }
    else
    {
        this->internalTick(synchronizedTick);
    }
}

bool FDActivity::hasFinished()
{
    return _hasFinished;
}

void FDActivity::initialize()
{
    
}