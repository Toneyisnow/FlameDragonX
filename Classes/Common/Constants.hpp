//
//  Constants.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef Constants_hpp
#define Constants_hpp

#include <stdio.h>
#include "cocos2d.h"

typedef unsigned char FDBYTE;

typedef enum Direction
{
    DirectionNone = 0,
    DirectionUp = 1,
    DirectionDown = 2,
    DirectionLeft = 3,
    DirectionRight = 4
} Direction;


class Constants : public cocos2d::Ref
{
public:
    
    static const int GAME_FPS = 50;
    
    static const int TickPerFrame_IdleAnimation = 15;
    static const int TickPerFrame_MoveAnimation = 5;
    
    constexpr static const float CREATURE_MOVE_SPEED = 0.6f;
    constexpr static const float CURSOR_MOVE_SPEED = 2.5f;
    constexpr static const float MENU_MOVE_SPEED = 3.0f;
    
    
    static const int LEVEL_COUNT = 30;
    
};


#endif /* Constants_hpp */
