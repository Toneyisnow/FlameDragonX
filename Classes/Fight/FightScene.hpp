//
//  FightingScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef FightScene_hpp
#define FightScene_hpp


#include "cocos2d.h"
#include "CounterScene.hpp"
#include "FightResult.hpp"
#include "FightAnimation.hpp"
#include "CombinedAnimate.hpp"

class FightScene : public CounterScene
{
private:
    
    Creature * _subject;
    Creature * _target;
    
    FightResult * _fightResult;
    
    ScaledSprite * _subjectSprite;
    ScaledSprite * _targetSprite;
    
    FightAnimation * _subjectAttackAnimation;
    FightAnimation * _subjectIdleAnimation;
    FightAnimation * _targetAttackAnimation;
    FightAnimation * _targetIdleAnimation;
    
    CombinedAnimate * _subjectAnimate;
    CombinedAnimate * _targetAnimate;
    
    void setTargetVisible(bool val);
    
    void takeTick(float dt) override;

    FDAnimate * generateAttackAnimate(Sprite * sprite, SlideAnimation * animation, int tag, SEL_CALLBACK2 onAttack);
    
public:
    
    FightScene(CounterInfo * info, FightResult * result);
    ~FightScene();
   
    void start() override;
    void alignSubjectTargetAnimation();
    
    void onSubjectAttack(Ref * frameObj);
    void onTargetAttack(Ref * frameObj);
    
};


#endif /* FightingScene_hpp */
