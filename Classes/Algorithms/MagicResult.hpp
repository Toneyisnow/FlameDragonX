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
    int _magicId;
    Vector<CounterResult *> _resultList;
    
public:
    
    MagicResult(Creature * c, int magicId, Vector<Creature *> t);
    ~MagicResult();
    
    int getMagicId();
    void appendResult(CounterResult * result);
    
    CounterObject * getCounterObject();
    CounterResult * getCounterResult(int index);
    
};

#endif /* MagicResult_hpp */
