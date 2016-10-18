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
    
    
};

#endif /* AIDelegate_hpp */
