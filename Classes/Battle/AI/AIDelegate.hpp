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

class AIDelegate : public cocos2d::Ref
{
protected:
    AICreature * _creature;
    BattleScene * _battleScene;
    
public:
    
    AIDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction();
    
    
};

#endif /* AIDelegate_hpp */
