//
//  CreatureDyingCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef CreatureDyingCondition_hpp
#define CreatureDyingCondition_hpp


#include "EventCondition.hpp"
#include "Creature.hpp"

class CreatureDyingCondition : public EventCondition
{
private:
    
    int _creatureId;
    
    
public:
    
    CreatureDyingCondition(int creatureId);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* CreatureDyingCondition_hpp */
