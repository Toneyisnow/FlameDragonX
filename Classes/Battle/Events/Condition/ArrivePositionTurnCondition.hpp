//
//  ArrivePositionTurnCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef ArrivePositionTurnCondition_hpp
#define ArrivePositionTurnCondition_hpp


#include "EventCondition.hpp"
#include "Creature.hpp"
#include "ArrivePositionCondition.hpp"

class ArrivePositionTurnCondition : public ArrivePositionCondition
{
private:
    
    
public:
    
    ArrivePositionTurnCondition(int creatureId, Vec2 position);
    
    bool isMatch(BattleScene * scene) override;
    
};

#endif /* ArrivePositionTurnCondition_hpp */
