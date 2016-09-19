//
//  TeamEliminatedCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef TeamEliminatedCondition_hpp
#define TeamEliminatedCondition_hpp


#include "EventCondition.hpp"
#include "Creature.hpp"

class TeamEliminatedCondition : public EventCondition
{
private:
    
    CreatureType _teamType;
    
    
public:
    
    TeamEliminatedCondition(CreatureType teamType);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* TeamEliminatedCondition_hpp */
