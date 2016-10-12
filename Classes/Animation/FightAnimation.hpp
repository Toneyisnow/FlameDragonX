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
    
    CounterScene * _scene;
    int _tagIndex;
    
public:
  
    FightAnimation(FightAnimationDefinition * def);
    
    bool isRemoteAttack();
    
    void setTagIndex(int tag);
    void setCounterScene(CounterScene * scene);
    
};

#endif /* FightAnimation_hpp */
