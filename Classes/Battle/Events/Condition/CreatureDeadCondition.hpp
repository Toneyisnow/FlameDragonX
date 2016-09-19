//
//  CreatureDeadCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef CreatureDeadCondition_hpp
#define CreatureDeadCondition_hpp


#include "EventCondition.hpp"
#include "Creature.hpp"

class CreatureDeadCondition : public EventCondition
{
private:
    
    int _creatureId;
    
    
public:
    
    CreatureDeadCondition(int creatureId);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* CreatureDeadCondition_hpp */
