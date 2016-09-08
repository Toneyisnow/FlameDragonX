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

USING_NS_CC;

typedef void (Ref::*SEL_CALLBACK0)();
typedef void (Ref::*SEL_CALLBACK1)(int);
typedef void (Ref::*SEL_CALLBACK2)(Ref*);

#define CALLBACK0_SELECTOR(_SELECTOR) static_cast<SEL_CALLBACK0>(&_SELECTOR)
#define CALLBACK1_SELECTOR(_SELECTOR) static_cast<SEL_CALLBACK1>(&_SELECTOR)
#define CALLBACK2_SELECTOR(_SELECTOR) static_cast<SEL_CALLBACK2>(&_SELECTOR)

class CallbackMethod : public cocos2d::Ref
{
private:
    
    Ref* _target;
    SEL_CALLBACK0 _selector0;
    SEL_CALLBACK1 _selector1;
    SEL_CALLBACK2 _selector2;
    
    int _paramInt;
    Ref * _paramObject;
   
    CallbackMethod(Ref* target);
public:
    
    static CallbackMethod * create(Ref* target, SEL_CALLBACK0 selector);
    static CallbackMethod * create(Ref* target, SEL_CALLBACK1 selector, int value);
    static CallbackMethod * create(Ref* target, SEL_CALLBACK2 selector, Ref* parameter);
    
    CallbackMethod(Ref* target, SEL_CALLBACK0 selector);
    CallbackMethod(Ref* target, SEL_CALLBACK1 selector, int value);
    CallbackMethod(Ref* target, SEL_CALLBACK2 selector, Ref* parameter);
    ~CallbackMethod();
    
    void execute();
};


#endif /* CallbackMethod_hpp */
