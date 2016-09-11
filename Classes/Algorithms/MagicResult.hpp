//
//  MagicResult.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef MagicResult_hpp
#define MagicResult_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "CounterResult.hpp"
#include "CounterObject.hpp"

class MagicResult : public cocos2d::Ref
{
    
private:
    
    CounterObject * _counterObject;
    Vector<CounterResult *> _magicCounterList;
    
public:
    
    MagicResult();
    
    
    
};

#endif /* MagicResult_hpp */
