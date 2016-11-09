//
//  CreatureRecord.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "CreatureRecord.hpp"
#include "Creature.hpp"

CreatureRecord::CreatureRecord(Creature * creature)
{
    creatureType = creature->getType();
    definitionId = creature->getDefinition()->definitionId;
    creatureId   = creature->getId();
    
    _data = creature->creatureData();
    _data->retain();
}

CreatureRecord::~CreatureRecord()
{
    _data->release();
}

CreatureData * CreatureRecord::creatureData()
{
    return _data;
}
