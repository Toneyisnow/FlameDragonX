//
//  CreatureRecord.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "CreatureRecord.hpp"
#include "Creature.hpp"

CreatureRecord::CreatureRecord(Creature * creature, bool cleanUpStatus)
{
    creatureType = creature->getType();
    definitionId = creature->getDefinition()->definitionId;
    creatureId   = creature->getId();
    
    _data = creature->creatureData();
    _data->retain();
    
    if (cleanUpStatus) {
        
        if (_data->hpCurrent > 0) {
            _data->hpCurrent = _data->hpMax;
        }
        
        _data->mpCurrent = _data->mpMax;
        
        _data->statusEnhanceAp = 0;
        _data->statusEnhanceDp = 0;
        _data->statusEnhanceDx = 0;
        _data->clearStatusFrozen();
        _data->clearStatusPoisoned();
        _data->clearStatusProhibited();
    }
    
    
}

CreatureRecord::~CreatureRecord()
{
    _data->release();
}

CreatureData * CreatureRecord::creatureData()
{
    return _data;
}
