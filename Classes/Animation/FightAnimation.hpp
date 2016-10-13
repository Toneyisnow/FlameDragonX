//
//  FightAnimation.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#ifndef FightAnimation_hpp
#define FightAnimation_hpp

#include "cocos2d.h"
#include "SlideAnimation.hpp"
#include "FightAnimationDefinition.hpp"

class CounterScene;

class FightAnimation : public SlideAnimation
{
private:

    FightAnimationDefinition * _definition;
    
public:
  
    FightAnimation(FightAnimationDefinition * def);
    
    bool isRemoteAttack();
    
    
};

#endif /* FightAnimation_hpp */
