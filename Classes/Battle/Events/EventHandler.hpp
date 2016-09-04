//
//  EventHandler.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventHandler_hpp
#define EventHandler_hpp


#include "cocos2d.h"
#include "FDEvent.hpp"

class BattleScene;
class EventLoader;

class EventHandler : public cocos2d::Ref
{
private:
    
    BattleScene * _battleScene;
    
    Vector<FDEvent *> * _eventList;
    
    EventLoader * _eventLoader;
    
public:
    
    EventHandler(BattleScene * scene);
    ~EventHandler();
    
    void initFromDefinition(int chapterId);
    
    void notifyTurnEvents();
    void notifyTriggeredEvents();
    
    void addEvent(FDEvent * event);
    void deactiveEvent(int eventId);
    void reactiveEvent(int eventId);
    void setDependentEvent(int eventId, int dependOnEventId);
    
};
#endif /* EventHandler_hpp */
