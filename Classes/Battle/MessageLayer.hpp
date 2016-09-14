//
//  MessageLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/12/16.
//
//

#ifndef MessageLayer_hpp
#define MessageLayer_hpp

#include "cocos2d.h"
#include "Message.hpp"
#include "ActivityQueue.hpp"

USING_NS_CC;

class BattleScene;

class MessageLayer : public cocos2d::Layer
{
  
private:
    
    BattleScene * _battleScene;
    Message * _activeMessage;
    
    ActivityQueue * _activityQueue;
    
    Sprite * _sprite;
    
    EventListenerTouchOneByOne * _listener;
    
public:
    
    MessageLayer(BattleScene * scene);
    ActivityQueue * getActivityQueue();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);

    bool isActive();
    
    void showMessage(Message * message);
    void removeMessage();
    
    void takeTick(int synchronizedTick);

};

#endif /* MessageLayer_hpp */
