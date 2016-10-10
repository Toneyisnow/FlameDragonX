//
//  FightingScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef FightScene_hpp
#define FightScene_hpp


#include "cocos2d.h"
#include "CounterScene.hpp"
#include "FightResult.hpp"

class FightScene : public CounterScene
{
private:
    
    Creature * _subject;
    Creature * _target;
    
    FightResult * _fightResult;
    
    void takeTick(float dt) override;

public:
    
    FightScene(CounterInfo * info, FightResult * result);
    ~FightScene();
   
};


#endif /* FightingScene_hpp */
