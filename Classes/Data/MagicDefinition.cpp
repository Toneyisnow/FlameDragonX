//
//  MagicDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "MagicDefinition.hpp"
#include "GameFormula.hpp"

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

MagicType MagicDefinition::getType()
{
    return _type;
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

int MagicDefinition::apInvolvedRate()
{
    return _apInvolvedRate;
}

FDRange * MagicDefinition::getEffectScope()
{
    int min = (isCross() ? 1 : 0);
    return FDRange::rangeWithValues(min, _effectScope);
}

FDRange * MagicDefinition::getQuantityRange()
{
    return _quantityRange;
}

bool MagicDefinition::hasAnimation()
{
    return (_type == MagicType_Attack);
}

bool MagicDefinition::isCross()
{
    return (_definitionId == 116 || _definitionId == 119);
}

void MagicDefinition::takeOffensiveEffect(Creature * target)
{
    if (target == nullptr)
    {
        return;
    }
    
    switch (_definitionId) {
        case 301:
            GameFormula::actionedByProhibited(target);
            break;
        case 302:
            GameFormula::actionedByPoison(target);
            break;
        case 303:
            GameFormula::actionedByFrozen(target);
            break;
        default:
            break;
    }
}

void MagicDefinition::takeDefensiveEffect(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    switch (_definitionId) {
        case 401:
            GameFormula::actionedByEnhanceAp(target);
            break;
        case 402:
            GameFormula::actionedByEnhanceDp(target);
            break;
        case 403:
            GameFormula::actionedByEnhanceDx(target);
            break;
        case 404:
            target->creatureData()->clearStatusPoisoned();
            break;
        case 405:
            target->creatureData()->clearStatusFrozen();
            break;
        case 406:
            target->startTurn();
            break;
        case 407:
            GameFormula::actionedByEnhanceAp(target);
            GameFormula::actionedByEnhanceDp(target);
            GameFormula::actionedByEnhanceDx(target);
            break;
        case 408:
            // Don't know what is the effect
            break;
        default:
            break;
    }
}

bool MagicDefinition::isDefensiveUsefulByCreature(Creature * target)
{
    if (target == nullptr) {
        return false;
    }
    
    if (_definitionId / 100 == 2) {
        return (target->creatureData()->hpCurrent < target->creatureData()->hpMax);
    }
    
    switch (_definitionId) {
        case 401:
            return (target->creatureData()->statusEnhanceAp == 0);
        case 402:
            return (target->creatureData()->statusEnhanceDp == 0);
        case 403:
            return (target->creatureData()->statusEnhanceDx == 0);
        case 404:
            return (target->creatureData()->statusPoisoned > 0);
        case 405:
            return (target->creatureData()->statusFrozen > 0);
        default:
            break;
    }
    
    return false;
}

int MagicDefinition::baseExperience()
{
    switch (_definitionId) {
        case 401:
        case 402:
        case 403:
            return 4;
        case 406:
            return 8;
        case 301:
        case 302:
        case 303:
        case 404:
        case 405:
            return 4;
        case 407:
        case 408:
            return 3;
        case 501:
            return 10;
        default:
            break;
    }
    return 0;
}
