//
//  ExchangeItemTargetState.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/5/16.
//
//

#ifndef ExchangeItemTargetState_hpp
#define ExchangeItemTargetState_hpp

#include "cocos2d.h"
#include "ActionState.hpp"
#include "Creature.hpp"

class BattleScene;

class ExchangeItemTargetState : public ActionState
{
private:
    
    Creature * _creature;
    Creature * _target;
    int _itemIndex;
    
    void selectItemToExchangeBack();
    void confirmItemToExchangeBack(int itemIndex);
    
public:
    
    ExchangeItemTargetState();
    ~ExchangeItemTargetState();
    
    static ExchangeItemTargetState * create(BattleScene * scene, StateSession * session);
    
    void onEnterState();
    void onExitState();
    
    virtual void handleClickAt(Vec2 position) override;
    
};


#endif /* ExchangeItemTargetState_hpp */
