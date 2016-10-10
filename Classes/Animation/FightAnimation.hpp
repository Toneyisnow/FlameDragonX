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

class FightAnimation : public SlideAnimation
{
private:

    const int DEFAULT_INTERVAL = 10;
    
    FightAnimationDefinition * _definition;
    
public:
  
    FightAnimation(FightAnimationDefinition * def);
    
};

#endif /* FightAnimation_hpp */
