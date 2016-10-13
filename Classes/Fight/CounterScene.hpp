//
//  FightScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef CounterScene_hpp
#define CounterScene_hpp

#include "cocos2d.h"
#include "CounterInfo.hpp"
#include "CreatureInfoMessage.hpp"

class CounterScene : public cocos2d::Scene
{
protected:
    
    const int ZORDER_ENEMY = 1;
    const int ZORDER_ENEMYBAR = 2;
    const int ZORDER_FRIENDBAR = 3;
    const int ZORDER_TAI = 4;
    const int ZORDER_FRIEND = 5;
    
    CounterInfo * _information;
    
    Layer * _layer;
    int _tickCount;
    bool _isClosing;
    
    
    ScaledSprite * _taiSprite;
    
    CreatureInfoMessage * _subjectInfo;
    CreatureInfoMessage * _targetInfo;
    
    
public:
    
    CounterScene(CounterInfo * info);
    ~CounterScene();
    
    virtual void start();
    virtual void takeTick(float dt);
    
    void closeScene();
};

#endif /* FightScene_hpp */
