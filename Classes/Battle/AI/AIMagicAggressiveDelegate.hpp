//
//  AIMagicAggressiveDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#ifndef AIMagicAggressiveDelegate_hpp
#define AIMagicAggressiveDelegate_hpp

#include "cocos2d.h"
#include "AIActiveDelegate.hpp"

class AIMagicAggressiveDelegate : public AIActiveDelegate
{
private:
    
    bool _foundAvailableMagic;
    bool _foundAvailableTarget;
    
    void takeMagicAction();
    void takePendingAction();
    
public:
    
    AIMagicAggressiveDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction() override;
    
    
};

#endif /* AIMagicAggressiveDelegate_hpp */
