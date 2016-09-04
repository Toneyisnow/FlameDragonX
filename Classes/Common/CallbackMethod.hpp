//
//  CallbackMethod.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef CallbackMethod_hpp
#define CallbackMethod_hpp


#include "cocos2d.h"

class CallbackMethod : public cocos2d::Ref
{
private:
    
    std::function<void()> _method0;
    std::function<void(int)> _method1;
    
public:
    
    CallbackMethod(std::function<void()> method);
    CallbackMethod(std::function<void(int)> method);
    
    int parameterCount();
    
    void execute();
    void execute(int value);
};


#endif /* CallbackMethod_hpp */
