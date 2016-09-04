//
//  CallbackActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef CallbackActivity_hpp
#define CallbackActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"
#include "CallbackMethod.hpp"

USING_NS_CC;

class CallbackActivity : public FDActivity
{
private:
    
    CallbackMethod * _method;
    
    int _intParameter1;
    
public:
    
    CallbackActivity(CallbackMethod * _method);
    CallbackActivity(CallbackMethod * _method, int parameter);
    ~CallbackActivity();
    
    void internalTick(int synchronizeTick);
    
};
#endif /* CallbackActivity_hpp */
