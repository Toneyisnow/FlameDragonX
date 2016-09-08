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

class BattleScene : public cocos2d::Scene
{
    
private:
    
    int _synchronizedTickCount;
    
    BattleField *_battleField;
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
    ActivityQueue * getActivityQueue();
    
    // static BattleScene* loadByChapterRecord(ChapterRecord* record);
    // static BattleScene* loadByBattleRecord(BattleRecord* record);
    
    // BattleScene();
  
    int getTurnNumber();
    int getCurrentTurnType();
    
    // Activity Methods
    void moveAndOpenMenu(Creature * creature, RoutePoint * route);
    void showMenu(int menuIndex);
    void attackTo(Creature * creature, Creature * target);
    void magicTo(Creature * creature, Vector<Creature *> * creatureList);
    void useItem(Creature * creature, int itemIndex, Creature * target);
    void waiveTurn(Creature * creature);
    void creatureEndTurn(int creatureId);
    void startTurn();
    void takeAIMove();
    void takeAIAction(int creatureId);
    
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)());
    //// CallbackActivity * createFunctionActivity(void(BattleScene::* callBackFunction)(int), int intParameter);
                                                           
    void testCallMethod(std::function<void(int)> callback);
    void testCallBack0();
    void testCallBack1(int num);
    void testCallBack2(Ref* val);
    
};

#endif /* BattleScene_hpp */
