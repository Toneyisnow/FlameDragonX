//
//  MoveByAction.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#ifndef MoveByAction_hpp
#define MoveByAction_hpp

#include "cocos2d.h"
#include "FDAction.hpp"

USING_NS_CC;

class MoveByAction : public FDAction
{
private:
    
    int _totalTick;
    Vec2 _originalPosition;
    Vec2 _deltaPosition;
    bool _initialized;
    
    
public:
    
    static MoveByAction * create(Sprite * sprite, Vec2 byPosition, int tick);
    MoveByAction(Sprite * sprite, Vec2 byPosition, int tick);
    
    void takeTick(int synchronizedTick) override;
    void initialize();
    
};


#endif /* MoveByAction_hpp */
