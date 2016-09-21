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
    this->_hasFinished = false;
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
        this->_hasFinished = false;
    }
}

void FDAnimate::takeTick(int synchronizedTick)
{
    if (this->_animation == nullptr || _hasFinished)
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
        if (this->_currentTick >= this->_animation->getTotalTick())
        {
            if (this->_animation->isRepeatable())
            {
                this->_currentTick = 0;
            }
            else
            {
                _hasFinished = true;
                this->_currentTick = this->_animation->getTotalTick() - 1;
            }
        }
        tick = this->_currentTick;
    }
    
    FDFrame * frame = this->_animation->frameAtTick(tick);
    if (frame != nullptr)
    {
        frame->renderFrame(this->_sprite);
    }
    
}

bool FDAnimate::hasFinished()
{
    return _hasFinished;
}