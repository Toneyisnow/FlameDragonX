//
//  SelectItemTargetState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/4/16.
//
//

#ifndef SelectItemTargetState_hpp
#define SelectItemTargetState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
#include "Creature.hpp"
#include "ItemDefinition.hpp"

class BattleScene;

class SelectItemTargetState : public ActionState
{
private:
    
    bool canApplyOnCreature(ItemDefinition * item, Creature * target);

public:
    
    SelectItemTargetState();
    ~SelectItemTargetState();
    
    static SelectItemTargetState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};

#endif /* SelectItemTargetState_hpp */
