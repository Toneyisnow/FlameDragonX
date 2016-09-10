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
#include "FDRange.hpp"

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
    
    bool _hasMoved;
    bool _hasActioned;
    
    
    
public:
    
    Creature(CreatureType type);
    
    ~Creature();
    
    void initWithDefinition(int identity, int creatureId);
    
    int getId();
    
    
    CreatureData * creatureData();
    CreatureDefinition * getDefinition();
    
    CreatureType getType();
    
    void setDirection(Direction direction);
    void setFocus(bool isFocus);
    
    void endTurn();
    void startTurn();
    
    
    bool isVisible();
    bool canFly();
    bool isDead();
    bool isFrozen();
    
    bool hasTakenAction();
    
    FDRange * getAttackRange();
    
};

#endif /* Creature_hpp */
