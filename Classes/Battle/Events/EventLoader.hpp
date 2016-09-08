//
//  EventLoader.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventLoader_hpp
#define EventLoader_hpp

#include "cocos2d.h"
#include "FDEvent.hpp"

class BattleScene;
class EventHandler;

class EventLoader : public cocos2d::Ref
{
private:
    
    BattleScene * _battleScene;
    EventHandler * _eventHandler;
    
    int _generatedEventId;
    
public:
    
    EventLoader();
    ~EventLoader();
    
    void initWithScene(BattleScene * scene, EventHandler * eventHandler);
    
    virtual void loadEvents();
    
    int loadSingleEvent(EventCondition * condition, CallbackMethod * method);
    
    void loadTurnEvent(int turnNumber, int type, CallbackMethod * method);
    
    
};
#endif /* EventLoader_hpp */
