//
//  CombinedAnimation.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/11/16.
//
//

#ifndef CombinedAnimation_hpp
#define CombinedAnimation_hpp

#include "cocos2d.h"
#include "SlideAnimation.hpp"

class CombinedAnimation : public SlideAnimation
{
private:
    
    Vector<SlideAnimation *> _animationList;
    
public:
    
    CombinedAnimation();
    ~CombinedAnimation();
    
    void appendAnimation(SlideAnimation * animation);
    
    int getFrameCount() override;
    FDFrame * frameAtTick(int tick) override;
    int getTotalTick() override;
    
};

#endif /* CombinedAnimation_hpp */
