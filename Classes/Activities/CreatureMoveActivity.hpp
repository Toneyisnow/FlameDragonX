//
//  CreatureMoveActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#ifndef CreatureMoveActivity_hpp
#define CreatureMoveActivity_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "CombinedActivity.hpp"
#include "SimpleMoveActivity.hpp"
#include "RoutePoint.hpp"

class BattleField;

USING_NS_CC;

class CreatureMoveActivity : public CombinedActivity
{
private:
    
    BattleField * _field;
    Creature * _creature;
    
public:
    
    static CreatureMoveActivity * create(BattleField * field, Creature * creature, RoutePoint * route);
    static CreatureMoveActivity * create(BattleField * field, int creatureId, RoutePoint * route);
    
    CreatureMoveActivity(BattleField * field, Creature * creature);
    CreatureMoveActivity(BattleField * field, int creatureId);
    
    void appendPosition(Vec2 position);
    void appendPosition(int posX, int posY);
    
};
#endif /* CreatureMoveActivity_hpp */

