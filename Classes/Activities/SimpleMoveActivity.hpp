//
//  SimpleMoveActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef SimpleMoveActivity_hpp
#define SimpleMoveActivity_hpp

#include "cocos2d.h"
#include "BattleObject.hpp"
#include "FieldActivity.hpp"

USING_NS_CC;

class SimpleMoveActivity : public FieldActivity
{
private:
    
    BattleObject * _object;
    Vec2 _targetLocation;
    
    float _speed;
    int deltaX;
    int deltaY;
    
public:
    
    SimpleMoveActivity(BattleField * field, BattleObject * object, Vec2 toPosition);
    
    void initialize();
    void internalTick(int synchronizeTick);

};
#endif /* SimpleMoveActivity_hpp */
