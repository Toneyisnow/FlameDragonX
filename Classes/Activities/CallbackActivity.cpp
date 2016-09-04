//
//  CallbackActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "CallbackActivity.hpp"

CallbackActivity::CallbackActivity(CallbackMethod * method)
{
    this->_method = method;
    this->_method->retain();
}

CallbackActivity::CallbackActivity(CallbackMethod * method, int parameter)
{
    this->_method = method;
    this->_method->retain();
    
    _intParameter1 = parameter;
}

CallbackActivity::~CallbackActivity()
{
    this->_method->release();
}


void CallbackActivity::internalTick(int synchronizeTick)
{
    if (this->_method->parameterCount() == 0)
    {
        this->_method->execute();
    }
    
    if (this->_method->parameterCount() == 1)
    {
        this->_method->execute(_intParameter1);
    }
    
    
    _hasFinished = true;
}
