//
//  RecordMenuState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#ifndef RecordMenuState_hpp
#define RecordMenuState_hpp


#include "cocos2d.h"
#include "ActionState.hpp"
class BattleScene;

class RecordMenuState : public ActionState
{
private:
    
    
public:
    
    static RecordMenuState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* RecordMenuState_hpp */
