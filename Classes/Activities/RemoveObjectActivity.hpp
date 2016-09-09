//
//  RemoveObjectActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/8/16.
//
//

#ifndef RemoveObjectActivity_hpp
#define RemoveObjectActivity_hpp


#include "FieldActivity.hpp"
#include "Creature.hpp"

class RemoveObjectActivity : public FieldActivity
{
private:
    
    BattleObject * _object;
    FDActivity * _activity;
    
public:
    
    static RemoveObjectActivity * create(BattleField * field, BattleObject * obj);
    
    RemoveObjectActivity(BattleField * field, BattleObject * obj);
    
    void initialize();
    void internalTick(int synchronizedTick);
    
};

#endif /* RemoveObjectActivity_hpp */
