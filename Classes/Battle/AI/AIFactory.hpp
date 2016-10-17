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
class AIFactory : public cocos2d::Ref
{
public:
    
    static AIDelegate * generateAI(AICreature * aiCreature, BattleScene * scene);
    
    
};

#endif /* AIFactory_hpp */
