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
#include "Creature.hpp"

class BattleScene;
class EventHandler;

class EventLoader : public cocos2d::Ref
{
protected:
    
    BattleScene * _battleScene;
    EventHandler * _eventHandler;
    
    int _generatedEventId;
    
public:
    
    EventLoader();
    ~EventLoader();
    
    void initWithScene(BattleScene * scene, EventHandler * eventHandler);
    
    virtual void loadEvents();
    
    int loadSingleEvent(EventCondition * condition, CallbackMethod * method);
    
    int loadTurnEvent(int turnNumber, CreatureType type, SEL_CALLBACK0 function);
    void showTalkMessage(int chapterId, int conversationId, int sequenceId);
    void appendActivityMethod(SEL_CALLBACK0 function);
    
    
};
#endif /* EventLoader_hpp */
