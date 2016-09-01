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

class Constants : public cocos2d::Ref
{
public:
    
    static const int GAME_FPS = 50;
    static const int TickPerFrame_IdleAnimation = 15;
    static const int TickPerFrame_MoveAnimation = 5;
    constexpr static const float DEFAULT_MOVE_SPEED = 0.6f;
    
    
    static const int LEVEL_COUNT = 30;
    
};


#endif /* Constants_hpp */
