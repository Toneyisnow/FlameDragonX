//
//  TurnCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/16/16.
//
//

#ifndef TurnCondition_hpp
#define TurnCondition_hpp

#include "EventCondition.hpp"
#include "Creature.hpp"

class TurnCondition : public EventCondition
{
private:
    
    CreatureType _turnType;
    int _turnNumber;
    
    
public:
    
    TurnCondition(int number, CreatureType type);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* TurnCondition_hpp */
