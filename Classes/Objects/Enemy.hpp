//
//  Enemy.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/17/16.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"
#include "AICreature.hpp"


class Enemy : public AICreature
{
private:
    
public:
    
    Enemy();
    Enemy(AIType aiType);
    
    static Enemy * create(int creatureId, int definitionId);
    static Enemy * create(int creatureId, int definitionId, int dropItemId);
    
};

#endif /* Enemy_hpp */
