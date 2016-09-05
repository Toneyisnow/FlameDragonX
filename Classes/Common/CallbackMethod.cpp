//
//  CallbackMethod.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CallbackMethod.hpp"



/*
 bool TimerTargetSelector::initWithSelector(Scheduler* scheduler, SEL_SCHEDULE selector, Ref* target, float seconds, unsigned int repeat, float delay)
 {
 _scheduler = scheduler;
 _target = target;
 _selector = selector;
 setupTimerWithInterval(seconds, repeat, delay);
 return true;
 }
 
 void TimerTargetSelector::trigger(float dt)
 {
 if (_target && _selector)
 {
 (_target->*_selector)(dt);
 }
 }
 
 */

CallbackMethod::CallbackMethod(std::function<void()> method)
{
    this->_method0 = method;
    this->_method1 = nullptr;
}

CallbackMethod::CallbackMethod(std::function<void(int)> method)
{
    this->_method0 = nullptr;
    this->_method1 = method;
    
}

int CallbackMethod::parameterCount()
{
    if (this->_method0 != nullptr)
    {
        return 0;
    }
    
    if (this->_method1 != nullptr)
    {
        return 1;
    }
    
    return 0;
}

void CallbackMethod::execute()
{
    if (this->_method0 != nullptr)
    {
        this->_method0();
    }
}

void CallbackMethod::execute(int val)
{
    if (this->_method1 != nullptr)
    {
        this->_method1(val);
    }
}