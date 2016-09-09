//
//  Animate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "FDAnimate.hpp"

FDAnimate::FDAnimate(Sprite * sprite)
{
    this->_sprite = sprite;
    
    this->_animation = nullptr;
    this->_currentTick = 0;
}

FDAnimate::~FDAnimate()
{
}

void FDAnimate::setAnimation(SlideAnimation *ani)
{
    this->_animation = ani;
    
    if (this->_animation != nullptr && !this->_animation->isSynchronized())
    {
        this->_currentTick = 0;
    }
}

void FDAnimate::takeTick(int synchronizedTick)
{
    if (this->_animation == nullptr)
    {
        return;
    }
    
    int tick = 0;
    
    if (this->_animation->isSynchronized())
    {
        tick = synchronizedTick % this->_animation->getTotalTick();
    }
    else
    {
        this->_currentTick ++;
        if (this->_currentTick >= this->_animation->getTotalTick() && this->_animation->isRepeatable())
        {
            this->_currentTick = 0;
        }
        tick = this->_currentTick;
    }
    
    FDFrame * frame = this->_animation->frameAtTick(tick);
    if (frame != nullptr)
    {
        frame->renderFrame(this->_sprite);
    }
    
}