//
//  ArrivePositionCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef ArrivePositionCondition_hpp
#define ArrivePositionCondition_hpp



#include "EventCondition.hpp"
#include "Creature.hpp"

class ArrivePositionCondition : public EventCondition
{
private:
    
    int _creatureId;
    Vec2 _targetPosition;
    
public:
    
    ArrivePositionCondition(int creatureId, Vec2 position);
    
    virtual bool isMatch(BattleScene * scene) override;
    
};

#endif /* ArrivePositionCondition_hpp */
