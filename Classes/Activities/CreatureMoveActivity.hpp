//
//  CreatureMoveActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef CreatureMoveActivity_hpp
#define CreatureMoveActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"
#include "Creature.hpp"

class BattleField;

USING_NS_CC;

class CreatureMoveActivity : public FDActivity
{
private:
    
    const float DEFAULT_SPEED = 0.6f;
    
    BattleField * _battleField;
    
    Creature * _creature;
    Vec2 _targetLocation;
    
    float _speed;
    int deltaX;
    int deltaY;
    
public:
    
    CreatureMoveActivity(BattleField * field, Creature * creature, Vec2 toPosition);
    
    void initialize();
    void internalTick(int synchronizeTick);

};
#endif /* CreatureMoveActivity_hpp */
