//
//  FDNumber.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef FDNumber_hpp
#define FDNumber_hpp

#include "cocos2d.h"

USING_NS_CC;

class FDNumber : public Ref
{
private:
    int _value;
    
    
public:
    
    static FDNumber * numberWithInt(int val);
    FDNumber(int val);
    
    int getValue();
};

#endif /* FDNumber_hpp */
