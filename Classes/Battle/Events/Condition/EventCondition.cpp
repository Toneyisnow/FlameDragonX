//
//  EventCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventCondition.hpp"

EventType EventCondition::getEventType()
{
    return _type;
}

bool EventCondition::isMatch(BattleScene * scene)
{
    return false;
}
