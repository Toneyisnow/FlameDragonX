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

class EventLoader : public cocos2d::Ref
{
private:
    
    BattleScene * _battleScene;
    int _generatedEventId;
    
public:
    
    EventLoader();
    ~EventLoader();
    
    void initWithScene(BattleScene * scene);
    
    virtual void loadEvents();
    
    int loadSingleEvent(EventCondition * condition, void(EventLoader::* callBackMethod)() );
    
    void loadTurnEvent(int turnNumber, int type, void * callBackMethod);
    
    
};
#endif /* EventLoader_hpp */
