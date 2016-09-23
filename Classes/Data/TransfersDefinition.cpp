//
//  TransfersDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "TransfersDefinition.hpp"


TransfersDefinition * TransfersDefinition::readFromFile(TextFileReader *reader)
{
    TransfersDefinition * definition = new TransfersDefinition(reader);
    definition->autorelease();
    return definition;
}

TransfersDefinition::TransfersDefinition(TextFileReader * reader)
{
    _creatureDefId = reader->readInt();
    int count = reader->readInt();
    for (int i = 0; i < count; i++) {
        TransferDefinition * definition = TransferDefinition::readFromFile(_creatureDefId, reader);
        _transferList.pushBack(definition);
    }
}

int TransfersDefinition::creatureDefId()
{
    return _creatureDefId;
}


TransferDefinition * TransfersDefinition::getTransfer(int index)
{
    if (index < 0 || index >= _transferList.size())
    {
        return nullptr;
    }
    
    return _transferList.at(index);
}

int TransfersDefinition::totalCount()
{
    return _transferList.size();
}
