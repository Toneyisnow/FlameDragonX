//
//  SelectMagicTargetState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/14/16.
//
//

#ifndef SelectMagicTargetState_hpp
#define SelectMagicTargetState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
#include "RangeScopeResolver.hpp"

class BattleScene;

class SelectMagicTargetState : public ActionState
{
private:
    
    RangeScopeResolver * _resolver;
    
public:
    
    SelectMagicTargetState();
    ~SelectMagicTargetState();
    
    static SelectMagicTargetState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};
#endif /* SelectMagicTargetState_hpp */
