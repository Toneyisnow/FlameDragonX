//
//  AIMagicDefensiveDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#ifndef AIMagicDefensiveDelegate_hpp
#define AIMagicDefensiveDelegate_hpp

#include "cocos2d.h"
#include "AIActiveDelegate.hpp"

class AIMagicDefensiveDelegate : public AIActiveDelegate
{
private:
    
    bool _foundAvailableMagic;
    bool _foundAvailableTarget;
    
    void takeMagicAction();
    void takePendingAction();
    
public:
    
    AIMagicDefensiveDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction() override;
    
};

#endif /* AIMagicDefensiveDelegate_hpp */
