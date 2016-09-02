//
//  AnimationLibrary.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef AnimationLibrary_hpp
#define AnimationLibrary_hpp

#include "cocos2d.h"
#include "SlideAnimation.hpp"

USING_NS_CC;

class AnimationLibrary : public Ref
{
private:
    
    static AnimationLibrary * _instance;
    
    Map<std::string, SlideAnimation *> * _slideAnimationDictionary;
    
    
    std::string filenameForBattleFieldAnimation(int creatureAniId, int index);
    //// void loadWalkAnimationForCreature(int creatureAniId, Direction direction, int centerImageId);
    void loadIdleAnimation(int creatureAniId);
    void loadWalkAnimation(int creatureAniId, Direction direction);
    void loadScopeIndicatorAnimation();
    
    
public:
    
    AnimationLibrary();
    ~AnimationLibrary();
    
    static AnimationLibrary * getInstance();
    
    void preloadBattleAnimationsForCreature(int creatureAniId);
    
    
    
    SlideAnimation * getIdleAnimation(int creatureAniId);
    SlideAnimation * getWalkAnimation(int creatureAniId, Direction direction);
    SlideAnimation * getScopeIndicatorAnimation();
    
};
#endif /* AnimationLibrary_hpp */
