//
//  ActionDispatcher.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef StateDispatcher_hpp
#define StateDispatcher_hpp

#include "cocos2d.h"
#include "ActionState.hpp"

class BattleScene;
class ActionState;

USING_NS_CC;

class StateDispatcher : public cocos2d::Ref
{
private:
    
    ActionState * _currentState;
    BattleScene * _scene;
    
public:
    
    StateDispatcher(BattleScene * scene);
    ~StateDispatcher();
    
    void handleClickAt(Vec2 position);
    void onNotified();
    
};

#endif /* StateDispatcher_hpp */
