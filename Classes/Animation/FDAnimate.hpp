//
//  Animate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef FDAnimate_hpp
#define FDAnimate_hpp

#include "cocos2d.h"
#include "SlideAnimation.hpp"
#include "CallbackMethod.hpp"

USING_NS_CC;

class FDAnimate : public cocos2d::Ref
{
protected:
    
    Sprite * _sprite;
    SlideAnimation * _animation;
    
    int _currentTick;
    bool _hasFinished;
    
    int _tag;
    Ref * _callbackTarget;
    SEL_CALLBACK2 _callbackSelector;
    
    FDFrame * _lastFrame;
    
public:
    
    static FDAnimate * create(Sprite * sprite, SlideAnimation * ani);
    
    
    FDAnimate(Sprite * sprite);
    ~FDAnimate();
    
    void setAnimation(SlideAnimation *ani);
    
    virtual void takeTick(int synchronizedTick);
    
    virtual bool hasFinished();
    
    void setTag(int tag);
    int getTag();
    
    void setCallback(Ref * target, SEL_CALLBACK2 callback);
    
    virtual int getTotalTick();
};

#endif /* Animate_hpp */
