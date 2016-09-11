//
//  AttackInformation.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef CounterInfor_hpp
#define CounterInfor_hpp

#include "cocos2d.h"
#include "CallbackMethod.hpp"

class CounterInfo : public cocos2d::Ref
{
    
private:
    
    int _backgroundImageId;
    
    CallbackMethod * _callback;
    
public:
    
    CounterInfo(int backgroundImageId, CallbackMethod * method);
    ~CounterInfo();
    
    int getBackgroundImageId();
    CallbackMethod * getCallback();
    
};

#endif /* AttackInformation_hpp */
