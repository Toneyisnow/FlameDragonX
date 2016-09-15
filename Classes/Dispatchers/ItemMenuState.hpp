//
//  ItemMenuState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/14/16.
//
//

#ifndef ItemMenuState_hpp
#define ItemMenuState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
class BattleScene;

class ItemMenuState : public ActionState
{
private:
    
    
public:
    
    static ItemMenuState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* ItemMenuState_hpp */
