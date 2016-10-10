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
#include "FightAnimationDefinition.hpp"
#include "FightAnimation.hpp"

USING_NS_CC;

class AnimationLibrary : public Ref
{
private:
    
    static AnimationLibrary * _instance;
    
    Map<std::string, SlideAnimation *> * _slideAnimationDictionary;
    
    
    std::string filenameForBattleFieldAnimation(int creatureAniId, int index);
    //// void loadWalkAnimationForCreature(int creatureAniId, Direction direction, int centerImageId);
    
    void loadIdleAnimation(int creatureAniId, bool greyout);
    void loadWalkAnimation(int creatureAniId, Direction direction);
    void loadDeadAnimation(int creatureAniId);
    
    void loadScopeIndicatorAnimation();
    void loadMenuAnimation(int menuItemId);
    
    void loadFightAnimation(int animationId, FightAnimationType type);
    
public:
    
    AnimationLibrary();
    ~AnimationLibrary();
    
    static AnimationLibrary * getInstance();
    
    void preloadBattleAnimationsForCreature(int creatureAniId);
    
    
    // Creature
    SlideAnimation * getIdleAnimation(int creatureAniId, bool greyout);
    SlideAnimation * getWalkAnimation(int creatureAniId, Direction direction);
    SlideAnimation * getDeadAnimation(int creatureAniId);
    
    // Scope Indicator
    SlideAnimation * getScopeIndicatorAnimation();
    
    // Menu
    SlideAnimation * getMenuAnimation(int menuItemId);
    
    // Fight Animations
    FightAnimation * getFightAnimation(int animationId, FightAnimationType type);
    
};
#endif /* AnimationLibrary_hpp */
