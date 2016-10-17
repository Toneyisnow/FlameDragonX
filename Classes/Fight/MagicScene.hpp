//
//  MagicScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef MagicScene_hpp
#define MagicScene_hpp


#include "cocos2d.h"
#include "CounterScene.hpp"
#include "MagicResult.hpp"
#include "FightAnimation.hpp"
#include "CombinedActivity.hpp"
#include "AnimateActivity.hpp"

class MagicScene : public CounterScene
{
private:
    
    Creature * _subject;
    Vector<Creature *> _targetList;
    int _targetCount;
    MagicDefinition * _magic;
    
    // UI
    ScaledSprite * _subjectSprite;
    ScaledSprite * _targetSprite;
    ScaledSprite * _magicSprite;
    
    FightAnimation * _subjectSkillAnimation;
    FightAnimation * _subjectIdleAnimation;
    FightAnimation * _firstTargetIdleAnimation;
    FightAnimation * _lastTargetIdleAnimation;
    
    FightAnimation * _magicAnimation;
    
    CombinedActivity * _subjectAnimate;
    CombinedActivity * _firstTargetAnimate;
    CombinedActivity * _lastTargetAnimate;
    AnimateActivity * _magicAnimate;
    CombinedActivity * _switchingAnimate;
    
    MagicResult * _magicResult;
    
    bool _showingMagic;
    int _currentTargetIndex;
    bool _switchingTarget;
    bool _switchingTargetTick;
    bool _isMagicTriggered;
    
    void takeTick(float dt) override;
    void alignSubjectTargetAnimation(int targetIndex);

    
public:
    
    
    MagicScene(CounterInfo * info, MagicResult * result);
    ~MagicScene();
    
    void start() override;
    
    void onTriggerMagic(Ref * frameObj);
    
    void tickMagic();
    void tickSwitching();
};

#endif /* MagicScene_hpp */
