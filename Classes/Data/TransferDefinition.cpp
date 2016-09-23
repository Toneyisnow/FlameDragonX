//
//  TransferDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "TransferDefinition.hpp"

#include "FDRange.hpp"

TransferDefinition * TransferDefinition::readFromFile(int fromCreatureId, TextFileReader *reader)
{
    TransferDefinition * definition = new TransferDefinition(fromCreatureId, reader);
    definition->autorelease();
    return definition;
}

TransferDefinition::TransferDefinition(int fromCreatureId, TextFileReader * reader)
{
    this->_fromCreatureDefId = fromCreatureId;
    this->_toCreatureDefId = reader->readInt();
    this->_transferId = this->_toCreatureDefId;
    this->_requireItemId = reader->readInt();
    
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

    this->_mvRange = reader->readRange();
    this->_mvRange->retain();
}

int TransferDefinition::transferId()
{
    return _transferId;
}

int TransferDefinition::fromCreatureDefId()
{
    return _fromCreatureDefId;
}

int TransferDefinition::toCreatureDefId()
{
    return _toCreatureDefId;
}

int TransferDefinition::requireItemId()
{
    return _requireItemId;
}

FDRange * TransferDefinition::hpRange()
{
    return _hpRange;
}

FDRange * TransferDefinition::mpRange()
{
    return _mpRange;
}

FDRange * TransferDefinition::apRange()
{
    return _apRange;
}

FDRange * TransferDefinition::dpRange()
{
    return _dpRange;
}

FDRange * TransferDefinition::dxRange()
{
    return _dxRange;
}

FDRange * TransferDefinition::mvRange()
{
    return _mvRange;
}

