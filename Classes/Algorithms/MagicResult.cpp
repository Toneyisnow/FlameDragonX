//
//  MagicResult.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "MagicResult.hpp"

MagicResult::~MagicResult()
{
    this->_counterObject->release();
    _resultList.clear();
}

MagicResult::MagicResult(Creature * c, int magicId, Vector<Creature *> t)
{
    this->_counterObject = new CounterObject(c);
    _magicId = magicId;
    
    for (Creature * target : t)
    {
        this->_counterObject->addTarget(target);
    }
    
}

void MagicResult::appendResult(CounterResult * result)
{
    _resultList.pushBack(result);
}

CounterResult * MagicResult::getCounterResult(int index)
{
    if (index < 0 || index >= _resultList.size())
    {
        throw new exception();
    }
    
    return _resultList.at(index);
}

CounterObject * MagicResult::getCounterObject()
{
    return this->_counterObject;
}

int MagicResult::getMagicId()
{
    return _magicId;
}
