//
//  LevelUpMagicDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "LevelUpMagicDefinition.hpp"


LevelUpMagicDefinition * LevelUpMagicDefinition::readFromFile(TextFileReader *reader)
{
    int definitionId = reader->readInt();
    if (definitionId < 0) {
        return nullptr;
    }
    
    LevelUpMagicDefinition * definition = new LevelUpMagicDefinition(definitionId, reader);
    definition->autorelease();
    return definition;
}

LevelUpMagicDefinition::LevelUpMagicDefinition(int defId, TextFileReader * reader)
{
    _definitionId = defId;
    _creatureLevel = reader->readInt();
    _magicId = reader->readInt();
    
}


int LevelUpMagicDefinition::definitionId()
{
    return _definitionId;
}

int LevelUpMagicDefinition::creatureLevel()
{
    return _creatureLevel;
}

int LevelUpMagicDefinition::magicId()
{
    return _magicId;
}
