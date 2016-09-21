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

void FightResult::setAttackInfo1(CounterResult* result)
{
    _attackInfo1 = result;
    _attackInfo1->retain();
}

void FightResult::setAttackInfo2(CounterResult* result)
{
    _attackInfo2 = result;
    _attackInfo2->retain();
}

void FightResult::setFightBackInfo1(CounterResult* result)
{
    _fightBackInfo1 = result;
    _fightBackInfo1->retain();
}

void FightResult::setFightBackInfo2(CounterResult* result)
{
    _fightBackInfo2 = result;
    _fightBackInfo2->retain();
}
