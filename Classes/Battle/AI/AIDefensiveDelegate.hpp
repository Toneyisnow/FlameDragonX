//
//  AIDefensiveDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#ifndef AIDefensiveDelegate_hpp
#define AIDefensiveDelegate_hpp

#include "cocos2d.h"
#include "AIActiveDelegate.hpp"

class AIDefensiveDelegate : public AIActiveDelegate
{
private:
    
    int _defensiveItemIndex;
    Creature * _target;
    
    
    Creature * findDefensiveCandidateTarget(Vector<FDPoint *> &scopePositions);
    
    
public:
    
    AIDefensiveDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAction() override;
    
    void useItemToTarget();
    
};


#endif /* AIActiveDelegate_hpp */
