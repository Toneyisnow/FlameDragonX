//
//  EventMethod.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventMethod.hpp"

EventMethod::EventMethod(std::function<void()> method)
{
    this->_method = method;
}

EventMethod::EventMethod(std::function<void(void*)> method)
{
    
}

void EventMethod::doMethod()
{
    this->_method();
}