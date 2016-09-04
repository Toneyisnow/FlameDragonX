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
#include "CallbackMethod.hpp"

class BattleScene;

USING_NS_CC;

class FDEvent : public cocos2d::Ref
{
protected:
    
    EventType _type;
    int _eventId;
    bool _isActivated;
    
    EventCondition * _condition;
    
    CallbackMethod * _method;
    
    Vector<FDEvent *> * _dependenEvents;
    
public:
    
    FDEvent(int eventId);
    ~FDEvent();
    
    int getEventId();
    EventType getType();
    
    void initWithCondition(EventCondition * cond, CallbackMethod * method);
    
    bool isTriggered(BattleScene * scene);
    
    void doAction();
    
    void deactivate();
    void reactivate();
    bool isActiveEvent();
    
    void addDependentEvent(FDEvent * other);
    
};

#endif /* FDEvent_hpp */
