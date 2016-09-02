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

class BattleField;

USING_NS_CC;

class CreatureMoveActivity : public CombinedActivity
{
private:
    
    BattleField * _field;
    Creature * _creature;
    
public:
    
    CreatureMoveActivity(BattleField * field, Creature * creature);
    
    void appendPosition(Vec2 position);
    void appendPosition(int posX, int posY);
    
};
#endif /* CreatureMoveActivity_hpp */

