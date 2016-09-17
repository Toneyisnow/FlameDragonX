//
//  BattleScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include "cocos2d.h"
#include "ChapterRecord.hpp"
#include "BattleRecord.hpp"
#include "BattleField.hpp"
#include "FDActivity.hpp"
#include "ActivityQueue.hpp"
#include "EventHandler.hpp"
#include "RoutePoint.hpp"
#include "CallbackActivity.hpp"
#include "CounterObject.hpp"
#include "MessageLayer.hpp"

class BattleScene : public cocos2d::Scene
{
    
private:
    
    int _chapterId;
    int _synchronizedTickCount;
    
    BattleField *_battleField;
    MessageLayer * _messageLayer;
    
    ActivityQueue * _activityQueue;
    EventHandler * _eventHandler;
    
    int _turnNumber;
    CreatureType _currentTurnType;
    
    void takeDeltaTimeTck(float dt);
    void takeTick(int synchronizedTick);
    
    void appendMethodToActivity(SEL_CALLBACK0 selector);
    void appendMethodToActivity(SEL_CALLBACK1 selector, int value);
    void appendMethodToActivity(SEL_CALLBACK2 selector, Ref* parameter);
    
    
    
public:
    
    BattleScene(ChapterRecord * chapterRecord);
    BattleScene(BattleRecord * battleRecord);
    ~BattleScene();
    
    
    BattleField * getBattleField();
    MessageLayer * getMessageLayer();
    ActivityQueue * getActivityQueue();
    
    // static BattleScene* loadByChapterRecord(ChapterRecord* record);
    // static BattleScene* loadByBattleRecord(BattleRecord* record);
    
    // BattleScene();
  
    int getTurnNumber();
    CreatureType getCurrentTurnType();
    
    // Activity Methods
    void moveAndOpenMenu(Creature * creature, RoutePoint * route);
    void showMenu(int menuIndex);
    void attackTo(Creature * creature, Creature * target);
    void magicTo(Creature * creature, int magicIndex, Vector<Creature *> * creatureList);
    void postFightAction(Ref * counterObject);
    void useItem(Creature * creature, int itemIndex, Creature * target);
    void waiveTurn(Creature * creature);
    void creatureEndTurn(Ref * creatureObj);
    void startTurn();
    void takeAIMove();
    void takeAIAction(int creatureId);
    
    void showMessage(Message * message);
    
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)());
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)(int), int intParameter);
                                                           
    void testCallMethod(std::function<void(int)> callback);
    void testCallBack0();
    void testCallBack1(int num);
    void testCallBack2(Ref* val);
    
};

#endif /* BattleScene_hpp */
