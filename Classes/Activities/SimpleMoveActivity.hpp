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
#include "Creature.hpp"
#include "FieldActivity.hpp"

USING_NS_CC;

class SimpleMoveActivity : public FieldActivity
{
private:
    
    Creature * _creature;
    Vec2 _targetLocation;
    
    float _speed;
    int deltaX;
    int deltaY;
    
public:
    
    SimpleMoveActivity(BattleField * field, Creature * creature, Vec2 toPosition);
    
    void initialize();
    void internalTick(int synchronizeTick);

};
#endif /* SimpleMoveActivity_hpp */
