//
//  Npc.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "Npc.hpp"


Npc::Npc()
: AICreature(CreatureType_Npc)
{
    
}

Npc * Npc::create(int creatureId, int definitionId)
{
    Npc * npc = new Npc();
    npc->initWithDefinition(creatureId, definitionId);
    npc->autorelease();
    return npc;
}

