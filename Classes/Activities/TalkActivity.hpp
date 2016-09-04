//
//  TalkActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef TalkActivity_hpp
#define TalkActivity_hpp

#include "cocos2d.h"
#include "GlobalActivity.hpp"
#include "Creature.hpp"

class BattleScene;

class TalkActivity : public GlobalActivity
{
private:
    
    Creature * _creature;
    std::string _message;
    
public:
    
    static TalkActivity * create(BattleScene * scene, Creature * creature, std::string message);
    TalkActivity(BattleScene * scene, Creature * creature, std::string message);
    
    void initialize();
    void internalTick(int synchronizedTick);
    
};

#endif /* TalkActivity_hpp */
