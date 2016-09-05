//
//  BattleScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "BattleScene.hpp"
#include "BattleField.hpp"
#include "ChapterRecord.hpp"
#include "AnimationLibrary.hpp"
#include "Constants.hpp"
#include "DataStore.hpp"
#include "MoneyItemDefinition.hpp"
#include "CreatureMoveActivity.hpp"
#include "CallbackActivity.hpp"
#include "TalkActivity.hpp"
#include "CreatureDeadActivity.hpp"

USING_NS_CC;

BattleScene::BattleScene(ChapterRecord* record)
{
    DataStore::getInstance()->loadData();
    _activityQueue = new ActivityQueue();
    
    _battleField = new BattleField(this);
    _battleField->initWithChapter(record->getChapterId());
    
    // add layer as a child to scene
    this->addChild(_battleField);
    
    //layer->initWithChapter(record->getChapterId());
    
    _eventHandler = new EventHandler(this);
    _eventHandler->initFromDefinition(record->getChapterId());
    
    
    
    _synchronizedTickCount = 0;
    schedule(CC_SCHEDULE_SELECTOR(BattleScene::takeDeltaTimeTck), 1.0 / Constants::GAME_FPS);
    
    _turnNumber = 0;
    startTurn();
    
    //////// Test Functions
    
    CreatureDefinition * def = DataStore::getInstance()->getCreatureDefinition(3);
    CreatureDefinition * def2 = DataStore::getInstance()->getCreatureDefinition(50508);
    
    MoneyItemDefinition * item = (MoneyItemDefinition *)DataStore::getInstance()->getItemDefinition(901);
    
    log("Definition of 50508: Ani=%d EX=%d", def2->animationId, def2->initialEX);
    
    //// UserDefault::getInstance()->setIntegerForKey(<#const char *key#>, <#int value#>)
    
    auto type = &BattleScene::testCallBack;
    
    auto fund = &BattleScene::showMenu;
    // std::function<void(int)> method = std::bind(&BattleScene::testCallBack, this, std::placeholders::_1);
    std::function<void(int)> method = std::bind(fund, this, std::placeholders::_1);
    testCallMethod(method);
    
    
    
}

BattleScene::BattleScene(BattleRecord * battleRecord)
{
                 
}
            
BattleScene::~BattleScene()
{
    _battleField->release();
    
    _activityQueue->release();
}

BattleField * BattleScene::getBattleField()
{
    return this->_battleField;
}

ActivityQueue * BattleScene::getActivityQueue()
{
    return this->_activityQueue;
}


void BattleScene::takeDeltaTimeTck(float dt)
{
    this->takeTick(_synchronizedTickCount ++);
    if (_synchronizedTickCount > 1000000)
    {
        _synchronizedTickCount = 0;
    }
    
}

void BattleScene::takeTick(int synchronizedTick)
{
    this->_battleField->takeTick(synchronizedTick);
    this->_activityQueue->takeTick(synchronizedTick);
    
}

int BattleScene::getTurnNumber()
{
    return _turnNumber;
}

int BattleScene::getCurrentTurnType()
{
    return _currentTurnType;
}

/////////////// Actions ///////////////

void BattleScene::moveAndOpenMenu(Creature * creature, RoutePoint * route)
{
    // Move
    
    CreatureMoveActivity * moveActivity = CreatureMoveActivity::create(_battleField, creature, route);
    this->_activityQueue->appendActivity(moveActivity);
    
    CallbackActivity * showMenu = createFunctionActivity(&BattleScene::showMenu, 1);
    this->_activityQueue->appendActivity(showMenu);
    
}

void BattleScene::showMenu(int menuId)
{
    
}


void BattleScene::attackTo(Creature * creature, Creature * target)
{
    // Calculations on the Attack result
    
    
    // Turn to the flight scene
    
    // Show Dying Animation
    if (creature->isDead() || target->isDead())
    {
        CreatureDeadActivity * dead = CreatureDeadActivity::create(this->_battleField, creature);
        _activityQueue->appendActivity(dead);
    }
    
    // Show Talk messages
    TalkActivity * talk = TalkActivity::create(this, creature, "Test Message");
    _activityQueue->appendActivity(talk);
    
    // Triggered Events
    _eventHandler->notifyTriggeredEvents();
    
    // End Turn
    CallbackActivity * endTurn = createFunctionActivity(&BattleScene::creatureEndTurn, creature->getId());
    _activityQueue->appendActivity(endTurn);

}

void BattleScene::magicTo(Creature * creature, Vector<Creature *> * creatureList)
{
    // Calculations on the Attack result
    
    
    // Turn to the magic flight scene
    
    // Show Talk messages
    TalkActivity * talk = TalkActivity::create(this, creature, "Test Message");
    _activityQueue->appendActivity(talk);
    
    // Triggered Events
    _eventHandler->notifyTriggeredEvents();
    
    // End Turn
    CallbackActivity * endTurn = createFunctionActivity(&BattleScene::creatureEndTurn, creature->getId());
    _activityQueue->appendActivity(endTurn);

}
void BattleScene::useItem(Creature * creature, int itemIndex, Creature * target)
{
    // Caculates the effect
    
    
    // Use Animation
    
    // Show Talk messages
    TalkActivity * talk = TalkActivity::create(this, creature, "Test Message");
    _activityQueue->appendActivity(talk);
    
    // End Turn
    CallbackActivity * endTurn = createFunctionActivity(&BattleScene::creatureEndTurn, creature->getId());
    _activityQueue->appendActivity(endTurn);

}

void BattleScene::waiveTurn(Creature * creature)
{
    // Recovery Animation
    
    
    // Triggered Events. e.g. Found Treature
    _eventHandler->notifyTriggeredEvents();
    
    // End Turn
    CallbackActivity * endTurn = createFunctionActivity(&BattleScene::creatureEndTurn, creature->getId());
    _activityQueue->appendActivity(endTurn);

}

void BattleScene::creatureEndTurn(int creatureId)
{
    // Grey out the creature
    
    if (_currentTurnType == CreatureType_Enemy || _currentTurnType == CreatureType_Npc)
    {
        CallbackActivity * aiMove = createFunctionActivity(&BattleScene::takeAIMove);
        _activityQueue->appendActivity(aiMove);
    }
    
}
void BattleScene::startTurn()
{
    if (_turnNumber == 0)
    {
        _turnNumber = 1;
        _currentTurnType = CreatureType_Friend;
        
    }
    else
    {
        switch (_currentTurnType) {
        case CreatureType_Friend: _currentTurnType = CreatureType_Npc;
            break;
        case CreatureType_Npc: _currentTurnType = CreatureType_Enemy;
            break;
        case CreatureType_Enemy: _currentTurnType = CreatureType_Friend;
            _turnNumber ++;
            break;
            
        default:
            break;
        }
    }
    
    // Grey back all creatures
    
    // Turn Events
    _eventHandler->notifyTurnEvents();
    
    // Turn Label Activity
    
    //
    if (_currentTurnType == CreatureType_Friend)
    {
        // Set Cursor Activity
    }
    else
    {
        CallbackActivity * aiMove = createFunctionActivity(&BattleScene::takeAIMove);
        _activityQueue->appendActivity(aiMove);
    }
}


void BattleScene::takeAIMove()
{
    // Find AI Creature
    Creature * target = _battleField->getCreatureById(101);
    
    if (target != nullptr)
    {
        // Take Move
        CreatureMoveActivity * activity = nullptr;
    
        //
        CallbackActivity * aiAction = createFunctionActivity(&BattleScene::takeAIAction, target->getId());
        _activityQueue->appendActivity(aiAction);
    }
    else
    {
        // Start Next Turn
        CallbackActivity * startTurn = createFunctionActivity(&BattleScene::startTurn);
        _activityQueue->appendActivity(startTurn);
    }
}
void BattleScene::takeAIAction(int creatureId)
{
    log("Take AI Action.");
    
    
    
}

CallbackActivity * BattleScene::createFunctionActivity(void(BattleScene::* callBackFunction)())
{
    std::function<void(int)> callback = std::bind(callBackFunction, this);
    CallbackMethod * method = new CallbackMethod(callback);
    CallbackActivity * call = new CallbackActivity(method);
    
    method->release();
    call->autorelease();
    
    return call;
}

CallbackActivity * BattleScene::createFunctionActivity(void(BattleScene::* callBackFunction)(int), int intParameter)
{
    std::function<void(int)> callback = std::bind(callBackFunction, this, std::placeholders::_1);
    CallbackMethod * method = new CallbackMethod(callback);
    CallbackActivity * call = new CallbackActivity(method, intParameter);
    
    method->release();
    call->autorelease();
    
    return call;
}


void BattleScene::testCallMethod(std::function<void(int)> callback)
{
    callback(4);
}

void BattleScene::testCallBack(int num)
{
    log("Called to here %d", num);
}