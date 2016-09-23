//
//  LevelUpDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "LevelUpDefinition.hpp"
#include "FDRange.hpp"

LevelUpDefinition * LevelUpDefinition::readFromFile(TextFileReader *reader)
{
    LevelUpDefinition * definition = new LevelUpDefinition(reader);
    definition->autorelease();
    return definition;
}

LevelUpDefinition::LevelUpDefinition(TextFileReader * reader)
{
    this->_definitionId = reader->readInt();
    
    this->_hpRange = reader->readRange();
    this->_hpRange->retain();
    
    this->_mpRange = reader->readRange();
    this->_mpRange->retain();
    
    this->_apRange = reader->readRange();
    this->_apRange->retain();
    
    this->_dpRange = reader->readRange();
    this->_dpRange->retain();
    
    this->_dxRange = reader->readRange();
    this->_dxRange->retain();
}

int LevelUpDefinition::definitionId()
{
    return _definitionId;
}

FDRange * LevelUpDefinition::hpRange()
{
    return _hpRange;
}

FDRange * LevelUpDefinition::mpRange()
{
    return _mpRange;
}

FDRange * LevelUpDefinition::apRange()
{
    return _apRange;
}

FDRange * LevelUpDefinition::dpRange()
{
    return _dpRange;
}

FDRange * LevelUpDefinition::dxRange()
{
    return _dxRange;
}

