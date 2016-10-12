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
#include "CombinedAnimation.hpp"

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
    
    CombinedAnimation * _subjectAnimation;
    CombinedAnimation * _targetAnimation;
    
    FDAnimate * _subjectAnimate;
    FDAnimate * _targetAnimate;
    
    Vec2 getBarLocation(Creature * creature);
    void setTargetVisible(bool val);
    
    void takeTick(float dt) override;

public:
    
    FightScene(CounterInfo * info, FightResult * result);
    ~FightScene();
   
    void start() override;
    void alignSubjectTargetAnimation();
    
};


#endif /* FightingScene_hpp */
