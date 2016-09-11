//
//  CounterInfo.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "CounterInfo.hpp"

CounterInfo::CounterInfo(int backgroundImageId, CallbackMethod * method)
{
    _backgroundImageId = backgroundImageId;
    _callback = method;
    
    if (_callback != nullptr)
    {
        _callback->retain();
    }
}

CounterInfo::~CounterInfo()
{
    if (_callback != nullptr)
    {
        _callback->release();
    }
}

int CounterInfo::getBackgroundImageId()
{
    return _backgroundImageId;
}

CallbackMethod * CounterInfo::getCallback()
{
    return _callback;
}
