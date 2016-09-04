//
//  CreatureDeadActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef CreatureDeadActivity_hpp
#define CreatureDeadActivity_hpp

#include "FieldActivity.hpp"
#include "Creature.hpp"

class CreatureDeadActivity : public FieldActivity
{
private:
    
    Creature * _creature;
    
public:
    
    static CreatureDeadActivity * create(BattleField * field, Creature * creature);
    
    CreatureDeadActivity(BattleField * field, Creature * creature);
    
    void initialize();
    void internalTick(int synchronizedTick);
    
};

#endif /* CreatureDeadActivity_hpp */
