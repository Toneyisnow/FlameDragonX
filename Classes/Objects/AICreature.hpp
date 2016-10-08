//
//  AICreatureData.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/30/16.
//
//

#ifndef AICreatureData_hpp
#define AICreatureData_hpp

#include "cocos2d.h"
#include "Creature.hpp"

typedef enum AIType {
    AIType_Idle,
    AIType_Aggressive,
    AIType_Defensive,
    AIType_Guard,
    AIType_Escape,
    AIType_StandBy,
    AIType_UnNoticable,
    AIType_Treasure
} AIType;


class AICreature : public Creature
{
private:
    
    AIType aiType;
    
    //// void aiParameter;
    
public:
    
    AICreature(CreatureType type);
    void wakeUpByAttack();
    
    int dropItemId;
};


#endif /* AICreatureData_hpp */
