//
//  CounterObject.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/11/16.
//
//

#ifndef CounterObject_hpp
#define CounterObject_hpp

#include "Creature.hpp"

class CounterObject : public cocos2d::Ref
{
    
private:
    
    Creature * _subject;
    Vector<Creature *> _targetList;
    
public:
    
    CounterObject(Creature * creature);
    ~CounterObject();
    
    void addTarget(Creature * target);
    
    Creature * getSubject();
    Vector<Creature *> getTargetList();
    
};

#endif /* CounterObject_hpp */
