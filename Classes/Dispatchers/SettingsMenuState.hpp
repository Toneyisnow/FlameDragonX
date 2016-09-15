//
//  SettingsMenuState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#ifndef SettingsMenuState_hpp
#define SettingsMenuState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
class BattleScene;

class SettingsMenuState : public ActionState
{
private:
    
    
public:
    
    static SettingsMenuState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* SettingsMenuState_hpp */
