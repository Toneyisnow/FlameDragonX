//
//  UsableItemDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#include "UsableItemDefinition.hpp"
#include "LocalizedStrings.hpp"
#include "Creature.hpp"

UsableItemDefinition * UsableItemDefinition::readFromFile(TextFileReader * reader)
{
    UsableItemDefinition * definition = new UsableItemDefinition();
    
    definition->initFromFile(reader);
    definition->autorelease();
    
    return definition;
}

void UsableItemDefinition::initFromFile(TextFileReader * reader)
{
    this->_definitionId = reader->readInt();
    
    /// this->name
    this->_name = LocalizedStrings::getInstance()->getItemName(_definitionId);
    
    this->_price = reader->readInt();
    this->_sellprice = reader->readInt();
    
    this->_useType = (UsableItemType)reader->readInt();
    this->_quantity = reader->readInt();
    
    this->_isReusable = (reader->readInt() == 1);
}

bool UsableItemDefinition::isReusable()
{
    return this->_isReusable;
}

void UsableItemDefinition::usedBy(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    switch (_useType) {
        case UsableItemType_Ap:
            target->creatureData()->ap += _quantity;
            break;
        case UsableItemType_Dp:
            target->creatureData()->dp += _quantity;
            break;
        case UsableItemType_Dx:
            target->creatureData()->dx += _quantity;
            break;
        case UsableItemType_Hp:
            target->creatureData()->updateHp(_quantity);
            break;
        case UsableItemType_Mp:
            target->creatureData()->updateMp(_quantity);
            break;
        case UsableItemType_Mv:
            target->creatureData()->mv += _quantity;
            break;
        case UsableItemType_MaxHp:
            target->creatureData()->hpMax += _quantity;
            break;
        case UsableItemType_MaxMp:
            target->creatureData()->mpMax += _quantity;
            break;
        case UsableItemType_EyeIce:
            
            break;
        case UsableItemType_EyeDark:
            
            break;
        case UsableItemType_EyeFire:
            
            break;
        case UsableItemType_EyeStar:
            
            break;
        case UsableItemType_AntiFreeze:
            target->creatureData()->clearStatusFrozen();
            break;
        case UsableItemType_AntiPoison:
            target->creatureData()->clearStatusPoisoned();
            break;
            
            
        default:
            break;
    }
}

bool UsableItemDefinition::onlyUseToSelf()
{
    return this->_definitionId >= 111 && this->_definitionId <= 115;
}

