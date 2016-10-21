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
    AIType_Treasure
} AIType;


class AICreature : public Creature
{
private:
    
    AIType _aiType;
    
    int _actionSpeed;
    
    bool _isUnnoticeableByOthers;
    
    //// void aiParameter;
    
    void generateActionSpeed();
    
public:
    
    AICreature(CreatureType type);
    AICreature(CreatureType type, AIType aiType);
    
    void initWithDefinition(int identity, int creatureId) override;
    
    
    void wakeUpByAttack();
    
    int dropItemId;
    
    AIType getAIType();
    
    int getActionSpeed();
    
    bool isAbleToAttack(Creature * another);
    bool isUnnoticeableByOthers();
    void setUnnoticeableByOthers(bool val);
    
};


#endif /* AICreatureData_hpp */
