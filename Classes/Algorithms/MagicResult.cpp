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
}

MagicResult::MagicResult(Creature * c, Vector<Creature *> t)
{
    this->_counterObject = new CounterObject(c);
    
    for (Creature * target : t)
    {
        this->_counterObject->addTarget(target);
    }
    
}

CounterObject * MagicResult::getCounterObject()
{
    return this->_counterObject;
}
