//
//  MoveByActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#ifndef MoveByActivity_hpp
#define MoveByActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

USING_NS_CC;

class MoveByActivity : public FDActivity
{
private:
    
    Sprite * _sprite;
    int _totalTick;
    int _currentTick;
    
    Vec2 _originalPosition;
    Vec2 _deltaPosition;
    
public:
    
    static MoveByActivity * create(Sprite * sprite, Vec2 byPosition, int tick);
    MoveByActivity(Sprite * sprite, Vec2 byPosition, int tick);
    
    void internalTick(int synchronizedTick) override;
    void initialize() override;
    
};
#endif /* MoveByActivity_hpp */
