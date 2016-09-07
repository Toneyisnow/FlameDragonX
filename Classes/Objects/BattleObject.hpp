//
//  BattleObject.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#ifndef BattleObject_hpp
#define BattleObject_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "FDAnimate.hpp"
#include "Constants.hpp"

USING_NS_CC;

typedef enum BattleObjectOrder
{
    BattleObjectOrder_OnGround = 10,
    BattleObjectOrder_Indicator = 20,
    BattleObjectOrder_Creature = 30,
    BattleObjectOrder_Menu = 40,
    BattleObjectOrder_FocusCreature = 50
} BattleObjectOrder;

typedef enum BattleObjectType
{
    BattleObject_ScopeIndicator,
    BattleObject_Cursor,
    BattleObject_Treasure,
    BattleObject_Menu,
    BattleObject_Creature
} BattleObjectType;

class BattleObject : public cocos2d::Ref
{
protected:
    
    BattleObjectType _objectType;
    
    Sprite * _baseSprite;
    
    FDAnimate * _animator;
    
    Direction _direction;
    
public:
    
    BattleObject(BattleObjectType type);
    ~BattleObject();
    
    BattleObjectType getObjectType();
    
    Sprite * getSprite();
    
    void initialize(std::string filename);
    
    void takeTick(int synchronizedTick);
    
    virtual void setDirection(Direction direction);
    
};

#endif /* BattleObject_hpp */
