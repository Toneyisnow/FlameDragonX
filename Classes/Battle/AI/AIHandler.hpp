//
//  AIFactory.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#ifndef AIFactory_hpp
#define AIFactory_hpp

#include "cocos2d.h"
#include "AICreature.hpp"
#include "AIDelegate.hpp"

class BattleScene;
class BattleField;

class AIHandler : public cocos2d::Ref
{
private:
    
    CreatureType _aiCreatureType;       // Should be Enemy or Npc
    BattleScene * _battleScene;
    BattleField * _battleField;
    

public:
    
    AIHandler(BattleScene * scene, CreatureType type);
    
    AICreature * findNextCreature();
    void takeAction(AICreature * creature);
    
};

#endif /* AIFactory_hpp */
