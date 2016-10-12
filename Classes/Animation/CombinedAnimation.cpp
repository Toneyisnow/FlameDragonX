//
//  CombinedAnimation.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/11/16.
//
//

#include "CombinedAnimation.hpp"

CombinedAnimation::CombinedAnimation()
: SlideAnimation(1, false, false)
{
    
}

CombinedAnimation::~CombinedAnimation()
{
    _animationList.clear();
}

void CombinedAnimation::appendAnimation(SlideAnimation * animation)
{
    _animationList.pushBack(animation);
}

int CombinedAnimation::getFrameCount()
{
    int totalFrame = 0;
    for (SlideAnimation * animation : _animationList)
    {
        totalFrame += animation->getFrameCount();
    }
    
    return totalFrame;
}

FDFrame * CombinedAnimation::frameAtTick(int tick)
{
    int restTick = tick;
    for (SlideAnimation * animation : _animationList) {
        if (restTick >= animation->getTotalTick()) {
            restTick -= animation->getTotalTick();
        } else {
            return animation->frameAtTick(restTick);
        }
    }
    
    return nullptr;
}

int CombinedAnimation::getTotalTick()
{
    int totalTick = 0;
    for (SlideAnimation * animation : _animationList)
    {
        totalTick += animation->getTotalTick();
    }
    
    return totalTick;
}



