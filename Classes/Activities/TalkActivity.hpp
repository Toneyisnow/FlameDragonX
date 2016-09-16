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

typedef enum TalkActivityType
{
    TalkActivityType_Talk,
    TalkActivityType_Speak
} TalkActivityType;

class BattleScene;

class TalkActivity : public GlobalActivity
{
private:
    
    TalkActivityType _type;
    Creature * _creature;
    std::string _message;
    
public:
    
    static TalkActivity * create(TalkActivityType type, BattleScene * scene, Creature * creature, std::string message);
    TalkActivity(TalkActivityType type, BattleScene * scene, Creature * creature, std::string message);
    
    void initialize();
    void internalTick(int synchronizedTick);
    
};

#endif /* TalkActivity_hpp */
