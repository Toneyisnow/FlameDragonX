//
//  CallbackMethod.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CallbackMethod.hpp"

USING_NS_CC;

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

CallbackMethod::CallbackMethod(Ref* target)
{
    this->_target = target;
    this->_target->retain();
    this->_selector0 = nullptr;
    this->_selector1 = nullptr;
    this->_selector2 = nullptr;
    
    _paramObject = nullptr;
}

CallbackMethod * CallbackMethod::create(Ref* target, SEL_CALLBACK0 selector)
{
    CallbackMethod * method = new CallbackMethod(target, selector);
    method->autorelease();
    return method;
}
CallbackMethod * CallbackMethod::create(Ref* target, SEL_CALLBACK1 selector, int param)
{
    CallbackMethod * method = new CallbackMethod(target, selector, param);
    method->autorelease();
    return method;
}

CallbackMethod * CallbackMethod::create(Ref* target, SEL_CALLBACK2 selector, Ref* param)
{
    CallbackMethod * method = new CallbackMethod(target, selector, param);
    method->autorelease();
    return method;
}

CallbackMethod::CallbackMethod(Ref* target, SEL_CALLBACK0 selector)
: CallbackMethod(target)
{
    this->_selector0 = selector;
}

CallbackMethod::CallbackMethod(Ref* target, SEL_CALLBACK1 selector, int param)
: CallbackMethod(target)
{
    this->_selector1 = selector;
    _paramInt = param;
}

CallbackMethod::CallbackMethod(Ref* target, SEL_CALLBACK2 selector, Ref * parameter)
: CallbackMethod(target)
{
    this->_selector2 = selector;
    _paramObject = parameter;
    _paramObject->retain();
}

CallbackMethod::~CallbackMethod()
{
    this->_target->release();
    
    if(_paramObject != nullptr)
    {
        _paramObject->release();
    }
}

void CallbackMethod::execute()
{
    if (_target == nullptr)
    {
        return;
    }
    
    if (_selector0 != nullptr)
    {
        (_target->*_selector0)();
    }
    else if (_selector1 != nullptr)
    {
        (_target->*_selector1)(_paramInt);
    }
    else if (_selector2 != nullptr)
    {
        (_target->*_selector2)(_paramObject);
    }
}

