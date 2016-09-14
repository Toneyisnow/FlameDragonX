//
//  SelectAttackTargetState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef SelectAttackTargetState_hpp
#define SelectAttackTargetState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
#include "RangeScopeResolver.hpp"


class BattleScene;

class SelectAttackTargetState : public ActionState
{
private:
    
    RangeScopeResolver * _resolver;
    
public:
    
    SelectAttackTargetState();
    ~SelectAttackTargetState();
    
    static SelectAttackTargetState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* SelectAttackTargetState_hpp */
