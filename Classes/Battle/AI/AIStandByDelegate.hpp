//
//  AIIdleDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#ifndef AIStandByDelegate_hpp
#define AIStandByDelegate_hpp

#include "cocos2d.h"
#include "AIDelegate.hpp"
#include "AICreature.hpp"

class AIStandByDelegate : public AIDelegate
{
private:
    
    
public:
    
    AIStandByDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction() override;
};

#endif /* AIIdleDelegate_hpp */
