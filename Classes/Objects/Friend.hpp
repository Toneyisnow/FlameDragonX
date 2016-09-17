//
//  Friend.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#ifndef Friend_hpp
#define Friend_hpp

#include "cocos2d.h"
#include "Creature.hpp"


class Friend : public Creature
{
private:
    
public:
    
    Friend();
    static Friend * create(int creatureId, int definitionId);

};

#endif /* Friend_hpp */
