//
//  CounterObject.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/11/16.
//
//

#include "CounterObject.hpp"


CounterObject::CounterObject(Creature * creature)
{
    this->_subject = creature;
    this->_subject->retain();
}

CounterObject::~CounterObject()
{
    this->_subject->release();
    this->_targetList.clear();
}

void CounterObject::addTarget(Creature * target)
{
    this->_targetList.pushBack(target);
}


Creature * CounterObject::getSubject()
{
    return this->_subject;
}

Vector<Creature *> CounterObject::getTargetList()
{
    return this->_targetList;
}