//
//  Npc.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef Npc_hpp
#define Npc_hpp


#include "cocos2d.h"
#include "AICreature.hpp"


class Npc : public AICreature
{
private:
    
public:
    
    Npc();
    
    static Npc * create(int creatureId, int definitionId);
    static Npc * create(int creatureId, int definitionId, int dropItemId);
    
};

#endif /* Npc_hpp */
