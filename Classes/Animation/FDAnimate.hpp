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

USING_NS_CC;

class FDAnimate : public cocos2d::Ref
{
private:
    
    Sprite * _sprite;
    SlideAnimation * _animation;
    
    int _currentTick;
    bool _hasFinished;
    
public:
    
    FDAnimate(Sprite * sprite);
    ~FDAnimate();
    
    void setAnimation(SlideAnimation *ani);
    
    void takeTick(int synchronizedTick);
    
    bool hasFinished();
    
};

#endif /* Animate_hpp */
