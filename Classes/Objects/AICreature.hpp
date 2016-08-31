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
    
    int dropItemId;
    
    AIType aiType;
    
    //// void aiParameter;
    
public:
    
    
    
};


#endif /* AICreatureData_hpp */