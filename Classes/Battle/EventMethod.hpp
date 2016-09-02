//
//  EventMethod.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventMethod_hpp
#define EventMethod_hpp

#include "cocos2d.h"

class EventMethod : public cocos2d::Ref
{
private:
    
    std::function<void()> _method;
    
public:
    
    EventMethod(std::function<void()> method);
    EventMethod(std::function<void(void*)> method);
    
    void doMethod();
};


#endif /* EventMethod_hpp */
