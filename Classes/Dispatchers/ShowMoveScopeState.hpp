//
//  ShowMoveScopeState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef ShowMoveScopeState_hpp
#define ShowMoveScopeState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
class BattleScene;

class ShowMoveScopeState : public ActionState
{
private:
    
    
public:
    
    static ShowMoveScopeState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    ActionState * handleClickAt(Vec2 position);
    
};

#endif /* ShowMoveScopeState_hpp */
