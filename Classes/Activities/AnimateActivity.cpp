//
//  AnimateActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#include "AnimateActivity.hpp"
#include "CallbackMethod.hpp"


AnimateActivity * AnimateActivity::create(Sprite * sprite, SlideAnimation * ani)
{
    AnimateActivity * animate = new AnimateActivity(sprite);
    animate->setAnimation(ani);
    animate->autorelease();
    
    return animate;
}

AnimateActivity::AnimateActivity(Sprite * sprite)
{
    this->_sprite = sprite;
    
    this->_animation = nullptr;
    this->_currentTick = 0;
    
    _callbackTarget = nullptr;
    _callbackSelector = nullptr;
    _tag = 0;
}

AnimateActivity::~AnimateActivity()
{
}

void AnimateActivity::reset()
{
    FDActivity::reset();
    this->_currentTick = 0;
}

void AnimateActivity::setAnimation(SlideAnimation *ani)
{
    this->_animation = ani;
    _lastFrame = nullptr;
    
    if (this->_animation != nullptr && !this->_animation->isSynchronized())
    {
        this->_currentTick = 0;
        this->_hasFinished = false;
    }
}

void AnimateActivity::internalTick(int synchronizedTick)
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

void AnimateActivity::setTag(int tag)
{
    _tag = tag;
}

int AnimateActivity::getTag()
{
    return _tag;
}

void AnimateActivity::setCallback(Ref * target, SEL_CALLBACK2 callback)
{
    _callbackTarget = target;
    _callbackSelector = callback;
}

int AnimateActivity::getTotalTick()
{
    return (_animation != nullptr) ? _animation->getTotalTick() : 0;
}
