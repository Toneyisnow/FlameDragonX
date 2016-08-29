//
//  CreatureDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "CreatureDefinition.hpp"

CreatureDefinition::CreatureDefinition(int defId)
{
    this->_definitionId = defId;
    this->_animationId = defId % 1000;
}

int CreatureDefinition::getDefinitionId()
{
    return _definitionId;
}
int CreatureDefinition::getAnimationId()
{
    return _animationId;
}