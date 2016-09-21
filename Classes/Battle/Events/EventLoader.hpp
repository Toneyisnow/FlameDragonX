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
class BattleField;
class EventHandler;

class EventLoader : public cocos2d::Ref
{
protected:
    
    BattleScene * _battleScene;
    BattleField * _battleField;
    EventHandler * _eventHandler;
    
    int _generatedEventId;
    
public:
    
    EventLoader();
    ~EventLoader();
    
    void initWithScene(BattleScene * scene, EventHandler * eventHandler);
    
    virtual void loadEvents();
    
    int loadSingleEvent(EventCondition * condition, CallbackMethod * method);
    
    
    ///// Helper Functions /////
    
    int loadTurnEvent(int turnNumber, CreatureType type, SEL_CALLBACK0 function);
    int loadDieEvent(int creatureId, SEL_CALLBACK0 function);
    int loadDyingEvent(int creatureId, SEL_CALLBACK0 function);
    int loadTeamEvent(CreatureType type, SEL_CALLBACK0 function);
    
    void showTalkMessage(int chapterId, int conversationId, int fromId, int toId);
    void showTalkMessage(int chapterId, int conversationId, int sequenceId);
    void appendActivityMethod(SEL_CALLBACK0 function);
    
    void BattleField_RemoveObject(Ref * obj);
    
    void gameOver();
    
    
};
#endif /* EventLoader_hpp */
