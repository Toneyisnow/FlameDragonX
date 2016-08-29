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

USING_NS_CC;

typedef enum BattleObjectOrder
{
    BattleObjectOrder_OnGround = 10,
    BattleObjectOrder_Indicator = 20,
    BattleObjectOrder_Creature = 30,
    BattleObjectOrder_Menu = 40,
    BattleObjectOrder_FocusCreature = 50
} BattleObjectOrder;


class BattleObject : public cocos2d::Ref
{
protected:
    
    Sprite * _baseSprite;
    
    FDAnimate * _animator;
    
public:
    
    BattleObject();
    ~BattleObject();
    
    Sprite * getSprite();
    
    void initialize();
    
    void takeTick(int synchronizedTick);
    
};

#endif /* BattleObject_hpp */
