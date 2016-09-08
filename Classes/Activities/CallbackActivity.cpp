//
//  CallbackActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CallbackActivity.hpp"

CallbackActivity * CallbackActivity::create(CallbackMethod * method)
{
    CallbackActivity * activity = new CallbackActivity(method);
    activity->autorelease();
    return activity;
}

CallbackActivity::CallbackActivity(CallbackMethod * method)
{
    this->_method = method;
    this->_method->retain();
}

CallbackActivity::~CallbackActivity()
{
    this->_method->release();
}


void CallbackActivity::internalTick(int synchronizeTick)
{
    this->_method->execute();
    
    _hasFinished = true;
}
