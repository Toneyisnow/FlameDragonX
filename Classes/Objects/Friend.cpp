//
//  Friend.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "Friend.hpp"

Friend::Friend()
: Creature(CreatureType_Friend)
{
    
}


Friend * Friend::create(int creatureId, int definitionId)
{
    Friend * f = new Friend();
    f->initWithDefinition(creatureId, definitionId);
    f->autorelease();
    return f;
}