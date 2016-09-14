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
#include "MoveScopeResolver.hpp"


class BattleScene;

class ShowMoveScopeState : public ActionState
{
private:
    
    MoveScopeResolver * _resolver;
    
public:
    
    ShowMoveScopeState();
    ~ShowMoveScopeState();
    
    static ShowMoveScopeState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* ShowMoveScopeState_hpp */
