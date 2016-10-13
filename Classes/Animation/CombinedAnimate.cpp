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
}

CombinedAnimate::~CombinedAnimate()
{
    _animateList.clear();
}

void CombinedAnimate::appendAnimate(FDAnimate * animate)
{
    _animateList.pushBack(animate);
}

void CombinedAnimate::takeTick(int synchronizedTick)
{
    if (_animateList.size() == 0) {
        _hasFinished = true;
        return;
    }
    
    FDAnimate * animate = _animateList.at(0);
    animate->takeTick(synchronizedTick);
    
    if (animate->hasFinished()) {
        _animateList.erase(0);
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
    return (_animateList.size() == 0) ? nullptr : _animateList.at(0);
}

bool CombinedAnimate::hasFinished()
{
    return (_animateList.size() == 0);
}

