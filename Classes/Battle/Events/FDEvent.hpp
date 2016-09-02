//
//  FDEvent.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef FDEvent_hpp
#define FDEvent_hpp

#include "cocos2d.h"
#include "EventCondition.hpp"
#include "EventMethod.hpp"

class BattleScene;

USING_NS_CC;

class FDEvent : public cocos2d::Ref
{
private:
    
    int _eventId;
    bool _isActivated;
    
    EventCondition * _condition;
    
    EventMethod * _method;
    
    Vector<FDEvent *> * _dependenEvents;
    
public:
    
    FDEvent(int eventId);
    ~FDEvent();
    
    int getEventId();
    void initWithCondition(EventCondition * cond, EventMethod * method);
    
    bool isTriggered(BattleScene * scene);
    
    void doAction();
    
    void deactivate();
    void reactivate();
    bool isActiveEvent();
    
    void addDependentEvent(FDEvent * other);
    
};

#endif /* FDEvent_hpp */
