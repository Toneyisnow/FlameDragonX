//
//  StartTurnCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef AnyTurnCondition_hpp
#define AnyTurnCondition_hpp


#include "EventCondition.hpp"
#include "Creature.hpp"

class AnyTurnCondition : public EventCondition
{
private:
    
    CreatureType _turnType;
    int _turnNumber;
    
    
public:
    
    AnyTurnCondition(CreatureType type);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* StartTurnCondition_hpp */
