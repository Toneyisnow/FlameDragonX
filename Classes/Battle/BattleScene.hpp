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
#include "AIHandler.hpp"

class BattleScene : public cocos2d::Scene
{
    
private:
    
    int _chapterId;
    int _synchronizedTickCount;
    
    int _totalMoney;
    
    BattleField *_battleField;
    MessageLayer * _messageLayer;
    
    ActivityQueue * _activityQueue;
    EventHandler * _eventHandler;
    
    int _turnNumber;
    CreatureType _currentTurnType;
    
    Creature * _currentTalkerFriend;
    Vector<FDNumber *> _currentDropItems;
    
    AIHandler * _enemyAIHander;
    AIHandler * _npcAIHander;
    
    void takeDeltaTimeTck(float dt);
    void takeTick(int synchronizedTick);
    
    void confirmItemFullExchange(int result);
    void confirmItemFullExchangeWithItem(int result);
    
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
    void magicTo(Creature * creature, int magicIndex, Vector<Creature *> creatureList);
    void postFightAction(Ref * counterObject);
    void useItem(Creature * creature, int itemIndex, Creature * target);
    void waiveTurn(Creature * creature);
    void creatureEndTurn(Ref * creatureObj);
    void startTurn();
    void waiveAllTurn();
    void takeAIMove();
    void takeAIAction(int creatureId);
    
    void showItemStatus(Ref * creature);
    void showMagicStatus(Ref * creature);
    
    void showMessage(Message * message);
    
    void appendMethodToActivity(SEL_CALLBACK0 selector);
    void appendMethodToActivity(SEL_CALLBACK1 selector, int value);
    void appendMethodToActivity(SEL_CALLBACK2 selector, Ref* parameter);
    void appendMethodToActivity(Ref * obj, SEL_CALLBACK0 selector);
    void appendMethodToActivity(Ref * obj, SEL_CALLBACK1 selector, int value);
    void appendMethodToActivity(Ref * obj, SEL_CALLBACK2 selector, Ref* parameter);
    void clearAllActivity();
    
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)());
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)(int), int intParameter);
    
    void gameWin();
    void gameOver();
    void gameCleared();
    
    
    void testCallMethod(std::function<void(int)> callback);
    void testCallBack0();
    void testCallBack1(int num);
    void testCallBack2(Ref* val);
    
};

#endif /* BattleScene_hpp */
