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

class FDActivity;

typedef enum BattleObjectOrder
{
    BattleObjectOrder_OnGround = 10,
    BattleObjectOrder_Indicator = 20,
    BattleObjectOrder_GroundCreature = 30,
    BattleObjectOrder_Cover = 40,
    BattleObjectOrder_HigherIndicator = 45,
    BattleObjectOrder_FlyCreature = 50,
    BattleObjectOrder_Menu = 60,

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
    
    bool _isRemoving;
    
public:
    
    BattleObject(BattleObjectType type);
    ~BattleObject();
    
    BattleObjectType getObjectType();
    
    Sprite * getSprite();
    
    void initialize(std::string filename);
    
    void takeTick(int synchronizedTick);
    
    virtual void setDirection(Direction direction);
    
    void setAnimation(SlideAnimation * animation);
    bool animationStopped();
    
    virtual FDActivity * onRemovalActivity();
    
    void setZOrder(int zOrder);
    
    bool isRemoving();
};

#endif /* BattleObject_hpp */
