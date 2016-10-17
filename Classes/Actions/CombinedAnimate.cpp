//
//  CombinedAnimate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/11/16.
//
//

#include "CombinedAnimate.hpp"

CombinedAnimate::CombinedAnimate(Sprite * sprite)
: FDAnimate(sprite)
{
    _animateList.clear();
    _currentAnimate = 0;
}

CombinedAnimate::~CombinedAnimate()
{
    _animateList.clear();
}

void CombinedAnimate::reset()
{
    for (FDAnimate * animate : _animateList) {
        animate->reset();
    }
    
    _currentAnimate = 0;
}

void CombinedAnimate::appendAnimate(FDAnimate * animate)
{
    _animateList.pushBack(animate);
}

void CombinedAnimate::takeTick(int synchronizedTick)
{
    if (_currentAnimate == _animateList.size()) {
        _hasFinished = true;
        return;
    }
    
    FDAnimate * animate = _animateList.at(_currentAnimate);
    animate->takeTick(synchronizedTick);
    
    if (animate->hasFinished()) {
        _currentAnimate++;
    }
}

int CombinedAnimate::getTotalTick()
{
    int totalTick = 0;
    for (FDAnimate * animate : _animateList)
    {
        totalTick += animate->getTotalTick();
    }
    
    return totalTick;
}

FDAnimate * CombinedAnimate::getCurrentAnimate()
{
    return (_animateList.size() <= _currentAnimate) ? nullptr : _animateList.at(_currentAnimate);
}

bool CombinedAnimate::hasFinished()
{
    return _hasFinished;
}

