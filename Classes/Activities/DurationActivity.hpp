//
//  DurationActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/18/16.
//
//

#ifndef DurationActivity_hpp
#define DurationActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

class DurationActivity : public FDActivity
{
private:
    
    int _tickCount;
    float _duration;
    
public:
    
    static DurationActivity * create(float duration);
    DurationActivity(float duration);
    
    void initialize() override;
    void internalTick(int synchronizedTick) override;
    
    
    
};

#endif /* DurationActivity_hpp */
