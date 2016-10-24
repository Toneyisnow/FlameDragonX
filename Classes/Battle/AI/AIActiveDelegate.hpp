//
//  AIActiveDelegate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#ifndef AIActiveDelegate_hpp
#define AIActiveDelegate_hpp

#include "cocos2d.h"
#include "AIDelegate.hpp"
#include "MoveScopeResolver.hpp"

class AIActiveDelegate : public AIDelegate
{
    
protected:
    
    Vector<Creature *> findAttackCandidateTargets();
    Vec2 findReachAttackPosition(Vector<FDPoint *> &scopePositions, Vector<Creature *> &candidateTargets);
    Vec2 findReachMovePosition(MoveScopeResolver * resolver, Vec2 targetPosition);
    
    Vec2 locatePathTargetPosition(Vec2 targetPosition);
    
    Vector<MagicDefinition *> getAvailableMagicList();
    Map<MagicDefinition *, Creature *> getCandidateMagicList(Vector<MagicDefinition *> & availableMagics);
    MagicDefinition * chooseMagicFromCandidate(std::vector<MagicDefinition *> magicList);
    Vec2 findOptimizedMagicPosition(MagicDefinition * magic, Creature * target);
    
    Creature * findOffensiveTarget(MagicDefinition * magic);
    Creature * findDefensiveTarget(MagicDefinition * magic);
    
    
public:
    
    AIActiveDelegate(AICreature * creature, BattleScene * scene);
    
    void takeAttackAction();

};

#endif /* AIActiveDelegate_hpp */
