//
//  ActionState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef ActionState_hpp
#define ActionState_hpp

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
    
public:
    
    ActionState();
    ~ActionState();
    
    virtual void initWithSession(BattleScene * scene, StateSession * session);
    
    virtual void onEnterState();
    virtual void onExitState();
    
    virtual ActionState * handleClickAt(Vec2 position);
    
};

#endif /* ActionState_hpp */
