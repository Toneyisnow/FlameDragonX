//
//  EventCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventCondition_hpp
#define EventCondition_hpp


#include "cocos2d.h"


typedef enum EventType
{
    EventTypeTurn,
    EventTypeTriggered
} EventType;


class BattleScene;

class EventCondition : public cocos2d::Ref
{
protected:
    
    EventType _type;
    
    
public:
    
    EventType getEventType();
    virtual bool isMatch(BattleScene * scene);
    
    
};

#endif /* EventCondition_hpp */
