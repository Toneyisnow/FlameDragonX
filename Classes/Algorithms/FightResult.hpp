//
//  FightStruct.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef FightResult_hpp
#define FightResult_hpp

#include "Creature.hpp"
#include "CounterResult.hpp"
#include "CounterObject.hpp"

class FightResult : public cocos2d::Ref
{
    
private:
    
    CounterObject * _counterObject;
    
    CounterResult _attackInfo1;
    CounterResult _attackInfo2;
    CounterResult _fightBackInfo1;
    CounterResult _fightBackInfo2;
    
public:
    
    FightResult(Creature * c, Creature * t);
    ~FightResult();
    
    CounterObject * getCounterObject();
    
};

#endif /* FightStruct_hpp */
