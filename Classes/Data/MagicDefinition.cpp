//
//  MagicDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "MagicDefinition.hpp"

MagicDefinition * MagicDefinition::readFromFile(TextFileReader * reader)
{
    MagicDefinition * definition = new MagicDefinition();
    
    definition->initFromFile(reader);
    definition->autorelease();
    
    return definition;
}

void MagicDefinition::initFromFile(TextFileReader * reader)
{
    this->_definitionId = reader->readInt();
    
    /// this->name
    
    this->_type = (MagicType)reader->readInt();
    int min = reader->readInt();
    int max = reader->readInt();
    this->_quantityRange = reader->readRange();
    this->_quantityRange->retain();
    
    if (_type == MagicType_Attack) {
        _apInvolvedRate = reader->readInt();
    }
    
    _hittingRate = reader->readInt();
    _effectScope = reader->readInt();
    _effectCoverage = reader->readInt();
    _mpCost = reader->readInt();
    _allowAfterMove = reader->readInt();
    _aiConsiderRate = reader->readInt();
}

int MagicDefinition::getDefinitionId()
{
    return _definitionId;
}

int MagicDefinition::effectScope()
{
    return _effectScope;
}

int MagicDefinition::effectCoverage()
{
    return _effectCoverage;
}

int MagicDefinition::hittingRate()
{
    return _hittingRate;
}

int MagicDefinition::mpCost()
{
    return _mpCost;
}

bool MagicDefinition::allowAfterMove()
{
    return _allowAfterMove;
}

int MagicDefinition::aiConsiderRate()
{
    return _aiConsiderRate;
}

int MagicDefinition::apInvovedRate()
{
    return _apInvolvedRate;
}

FDRange * MagicDefinition::getEffectScope()
{
    int min = (isCross() ? 1 : 0);
    return FDRange::rangeWithValues(min, _effectScope);
}


bool MagicDefinition::hasAnimation()
{
    return (_type == MagicType_Attack);
}

bool MagicDefinition::isCross()
{
    return (_definitionId == 116 || _definitionId == 119);
}