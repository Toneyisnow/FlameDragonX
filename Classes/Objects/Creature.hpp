//
//  Creature.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#ifndef Creature_hpp
#define Creature_hpp

#include "cocos2d.h"
#include "BattleObject.hpp"
#include "CreatureDefinition.hpp"
#include "CreatureData.hpp"


typedef enum CreatureType
{
    CreatureType_Friend,
    CreatureType_Enemy,
    CreatureType_Npc,
    
} CreatureType;

typedef enum GestureStatus {
    GestureStatus_Idle,
    GestureStatus_WalkingUp,
    GestureStatus_WalkingDown,
    GestureStatus_WalkingLeft,
    GestureStatus_WalkingRight
} GestureStatus;


class Creature : public BattleObject
{
private:
    
    int _identifier;
    int _creatureId;
    CreatureDefinition * _definition;
    CreatureData * _data;
    
    CreatureType _creatureType;
    GestureStatus _gestureStatus;
    
public:
    
    Creature(CreatureType type);
    
    ~Creature();
    
    void initWithDefinition(int identity, int creatureId);
    
    int getId();
    
    CreatureType getType();
    
    // Deprecated
    void setGesture(GestureStatus gesture);
    
    void setDirection(Direction direction);
    
    bool isDead();
    
};

#endif /* Creature_hpp */
