//
//  Animate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "FDAnimate.hpp"
#include "CallbackMethod.hpp"


FDAnimate * FDAnimate::create(Sprite * sprite, SlideAnimation * ani)
{
    FDAnimate * animate = new FDAnimate(sprite);
    animate->setAnimation(ani);
    animate->autorelease();
    
    return animate;
}

FDAnimate::FDAnimate(Sprite * sprite)
{
    this->_sprite = sprite;
    
    this->_animation = nullptr;
    this->_currentTick = 0;
    this->_hasFinished = false;
    
    _callbackTarget = nullptr;
    _callbackSelector = nullptr;
    _tag = 0;
}

FDAnimate::~FDAnimate()
{
}

void FDAnimate::setAnimation(SlideAnimation *ani)
{
    this->_animation = ani;
    _lastFrame = nullptr;
    
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
        
        if (_lastFrame != frame) {
            
            if (_callbackTarget != nullptr && _callbackSelector != nullptr) {
                CallbackMethod * method = CallbackMethod::create(_callbackTarget, _callbackSelector, frame);
                method->execute();
            }
            _lastFrame = frame;
        }
    }
}

bool FDAnimate::hasFinished()
{
    return _hasFinished;
}

void FDAnimate::setTag(int tag)
{
    _tag = tag;
}

int FDAnimate::getTag()
{
    return _tag;
}

void FDAnimate::setCallback(Ref * target, SEL_CALLBACK2 callback)
{
    _callbackTarget = target;
    _callbackSelector = callback;
}

int FDAnimate::getTotalTick()
{
    return (_animation != nullptr) ? _animation->getTotalTick() : 0;
}
