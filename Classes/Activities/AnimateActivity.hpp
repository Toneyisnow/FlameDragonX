//
//  AnimateActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#ifndef AnimateActivity_hpp
#define AnimateActivity_hpp

#include "cocos2d.h"
#include "SlideAnimation.hpp"
#include "CallbackMethod.hpp"
#include "FDActivity.hpp"

USING_NS_CC;

class AnimateActivity : public FDActivity
{
protected:
    
    Sprite * _sprite;
    SlideAnimation * _animation;
    
    int _currentTick;
    
    int _tag;
    Ref * _callbackTarget;
    SEL_CALLBACK2 _callbackSelector;
    
    FDFrame * _lastFrame;
    
public:
    
    static AnimateActivity * create(Sprite * sprite, SlideAnimation * ani);
    
    
    AnimateActivity(Sprite * sprite);
    ~AnimateActivity();
    
    virtual void reset() override;
    
    void setAnimation(SlideAnimation *ani);
    
    void internalTick(int synchronizedTick) override;
    
    void setTag(int tag);
    int getTag();
    
    void setCallback(Ref * target, SEL_CALLBACK2 callback);
    
    virtual int getTotalTick() override;
};

#endif /* AnimateActivity_hpp */
