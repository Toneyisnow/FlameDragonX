//
//  AIIdleDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#ifndef AIIdleDelegate_hpp
#define AIIdleDelegate_hpp

#include "cocos2d.h"
#include "AIDelegate.hpp"
#include "AICreature.hpp"

class AIIdleDelegate : public AIDelegate
{
private:
    
    
public:
    
    AIIdleDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction() override;
};

#endif /* AIIdleDelegate_hpp */
