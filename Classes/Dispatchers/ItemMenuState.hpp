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
#include "Creature.hpp"

class BattleScene;

class ItemMenuState : public ActionState
{
private:
    
    Creature * _creature;
    
public:
    
    static ItemMenuState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
    void selectItemToExchange();
    void confirmItemToExchange(int itemIndex);
    void selectItemToUse();
    void confirmItemToUse(int itemIndex);
    void selectItemToEquip();
    void confirmItemToEquip(int itemIndex);
    void selectItemToDrop();
    void confirmItemToDrop(int itemIndex);
    
};

#endif /* ItemMenuState_hpp */
