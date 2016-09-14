//
//  ActionState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef ActionState2_hpp
#define ActionState2_hpp

#include "cocos2d.h"
#include "StateSession.hpp"

USING_NS_CC;

class BattleScene;
class BattleField;

class ActionState : public cocos2d::Ref
{
protected:
    
    BattleScene * _battleScene;
    BattleField * _battleField;
    StateSession * _session;
    
    ActionState * _nextState;
    
public:
    
    ActionState();
    ~ActionState();
    
    virtual void initWithSession(BattleScene * scene, StateSession * session);
    
    ActionState * getNextState();
    
    virtual void onEnterState();
    virtual void onExitState();
    
    virtual void handleClickAt(Vec2 position);
    
};

#endif /* ActionState_hpp */
