//
//  ResolverHelper.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/20/16.
//
//

#ifndef ResolverHelper_hpp
#define ResolverHelper_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "BattleField.hpp"
#include "PointMap.hpp"

USING_NS_CC;

class ResolverHelper : public cocos2d::Ref
{
private:
    
    
public:
    
    static int calculateMovePoint(BattleField * battleField, Creature * creature, Vec2 position);
    static PointMap<Creature *> * calculateZocPositions(BattleField * battleField, Creature * creature);
    static float calculateHeuristicPoint(Vec2 current, Vec2 target);
    static bool isHostile(Creature * c1, Creature * c2);
    
};

#endif /* ResolverHelper_hpp */
