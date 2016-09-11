//
//  FightStruct.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "FightResult.hpp"

FightResult::FightResult(Creature * c, Creature * t)
{
    this->_counterObject = new CounterObject(c);
    this->_counterObject->addTarget(t);
    
}

FightResult::~FightResult()
{
    this->_counterObject->release();
}


CounterObject * FightResult::getCounterObject()
{
    return this->_counterObject;
}
