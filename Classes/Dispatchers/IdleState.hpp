//
//  IdleState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef IdleState_hpp
#define IdleState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
class BattleScene;

class IdleState : public ActionState
{
private:
    
    
public:
    
    static IdleState * create(BattleScene * scene);
    
    void onEnterState();
    void onExitState();
    
    ActionState * handleClickAt(Vec2 position);
    
};

#endif /* IdleState_hpp */
