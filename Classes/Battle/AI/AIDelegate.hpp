//
//  AIDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#ifndef AIDelegate_hpp
#define AIDelegate_hpp

#include "cocos2d.h"
#include "AICreature.hpp"

class BattleScene;
class BattleField;

class AIDelegate : public cocos2d::Ref
{
protected:
    AICreature * _creature;
    BattleScene * _battleScene;
    BattleField * _battleField;
    
public:
    
    AIDelegate(AICreature * creature, BattleScene * scene);
    
    virtual void takeAction();
    
    void takeWaiveAction();
    
    bool needRecover(Creature * creature);
    bool canRecover(Creature * creature);
    int getRecoverItemIndex(Creature * creature);
    
    Creature * locateNearestFriend();
    
    void setCreatureMoved(Vec2 position);
};

#endif /* AIDelegate_hpp */
