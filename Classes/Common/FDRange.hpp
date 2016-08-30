//
//  FDRange.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#ifndef FDRange_hpp
#define FDRange_hpp

#include "cocos2d.h"

class FDRange : public cocos2d::Ref
{
private:
    
    int _minValue;
    int _maxValue;
public:
    
    
    static FDRange * rangeWithValues(int min, int max);
    void initWithValues(int min, int max);
    
    bool containsValue(int val);
    
    int getMin();
    int getMax();
};

#endif /* FDRange_hpp */
