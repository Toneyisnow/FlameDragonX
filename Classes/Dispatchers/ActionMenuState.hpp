//
//  ActionMenuState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/8/16.
//
//

#ifndef ActionMenuState_hpp
#define ActionMenuState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
#include "Creature.hpp"

class ActionMenuState : public ActionState
{
private:
    
    Creature * _creature;
    
public:
    
    static ActionMenuState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    ActionState * handleClickAt(Vec2 position);
    
    void checkTreatureAndWaiveTurn();
    void confirmPickTreasure();
    
    
};

#endif /* ActionMenuState_hpp */
