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
#include "PointMap.hpp"
#include "GameFormula.hpp"
#include "FightScene.hpp"
#include "TalkMessage.hpp"

USING_NS_CC;

BattleScene::BattleScene(ChapterRecord* record)
{
    DataStore::getInstance()->loadData();
    _activityQueue = new ActivityQueue();
    
    _battleField = new BattleField(this);
    _battleField->initWithChapter(record->getChapterId());
    this->addChild(_battleField);
    
    _messageLayer = new MessageLayer(this);
    this->addChild(_messageLayer);
    
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
    
    
    CallbackMethod * me = new CallbackMethod(this, CALLBACK0_SELECTOR(BattleScene::testCallBack0));
    me->execute();
    
    CallbackMethod * me1 = new CallbackMethod(this, CALLBACK1_SELECTOR(BattleScene::testCallBack1), 5);
    me1->execute();
    
    CallbackMethod * me2 = new CallbackMethod(this, CALLBACK2_SELECTOR(BattleScene::testCallBack2), def);
    me2->execute();
    
    
    auto fund = &BattleScene::showMenu;
    // std::function<void(int)> method = std::bind(&BattleScene::testCallBack, this, std::placeholders::_1);
    std::function<void(int)> method = std::bind(fund, this, std::placeholders::_1);
    testCallMethod(method);
    
    PointMap<FDPoint *> * map = new PointMap<FDPoint *>();
    map->insert(Vec2(1, 2), FDPoint::create(Vec2(4, 4)));
    map->insert(Vec2(3, 2), FDPoint::create(Vec2(4, 4)));
    
    if (map->containsKey(Vec2(1, 2)))
    {
        FDPoint * result = map->at(Vec2(1, 2));
        log("Result %f %f", result->getValue().x, result->getValue().y);
    }
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
    
    
}

void BattleScene::showMenu(int menuId)
{
    
}


void BattleScene::attackTo(Creature * creature, Creature * target)
{
    log("Attack from %d to %d", creature->getId(), target->getId());
    
    // Calculations on the Attack result
    FightResult * result = GameFormula::dealWithFight(_battleField, creature, target);
    
    
    // Turn to the flight scene
    CallbackMethod * callback = CallbackMethod::create(this, CALLBACK2_SELECTOR(BattleScene::postFightAction), result->getCounterObject());
    CounterInfo * info = new CounterInfo(1, callback);
    FightScene * scene = new FightScene(info, result);
    
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));

    info->release();
    scene->release();
}

void BattleScene::magicTo(Creature * creature, int magicIndex, Vector<Creature *> * creatureList)
{
    log("Magic from %d.", creature->getId());
    
    // Calculations on the Attack result
    

    
    // Turn to the magic flight scene
    
}

void BattleScene::postFightAction(Ref * counterObjectObj)
{
    log("Enter postFightAction.");
    
    CounterObject * counterObject = (CounterObject *)counterObjectObj;
    
    Creature * creature = counterObject->getSubject();
    
    // Triggered Events
    _eventHandler->notifyTriggeredEvents();
    
    // Show Dying Animation
    if (creature->isDead())
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
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);

}

void BattleScene::useItem(Creature * creature, int itemIndex, Creature * target)
{
    // Caculates the effect
    
    
    // Use Animation
    
    // Show Talk messages
    TalkActivity * talk = TalkActivity::create(this, creature, "Test Message");
    _activityQueue->appendActivity(talk);
    
    // End Turn
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);
}

void BattleScene::waiveTurn(Creature * creature)
{
    // Recovery Animation
    
    
    
    // Triggered Events. e.g. Found Treature
    _eventHandler->notifyTriggeredEvents();
    
    // End Turn
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);

}

void BattleScene::creatureEndTurn(Ref * creatureObj)
{
    Creature * creature = (Creature *)creatureObj;
    
    // Grey out the creature
    creature->endTurn();
    
    if (_currentTurnType == CreatureType_Enemy || _currentTurnType == CreatureType_Npc)
    {
        this->appendMethodToActivity(CALLBACK0_SELECTOR(BattleScene::takeAIMove));
    }
    else
    {
        bool shouldEndTurn = true;
        for(Creature * creature : *(_battleField->getFriendList()))
        {
            if (!creature->hasTakenAction())
                shouldEndTurn = false;
        }
        
        if (shouldEndTurn)
        {
            this->appendMethodToActivity(CALLBACK0_SELECTOR(BattleScene::startTurn));
        }
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
        // Grey back all creatures
        Vector<Creature *> * lastCreaturelist;
        
        switch (_currentTurnType) {
        case CreatureType_Friend:
                _currentTurnType = CreatureType_Npc;
                lastCreaturelist = _battleField->getFriendList();
            break;
        case CreatureType_Npc:
                _currentTurnType = CreatureType_Enemy;
                lastCreaturelist = _battleField->getNPCList();
            break;
        case CreatureType_Enemy:
                _currentTurnType = CreatureType_Friend;
                lastCreaturelist = _battleField->getEnemyList();
                _turnNumber ++;
            break;
            
        default:
            break;
        }
        
        for (Creature * creature : *lastCreaturelist) {
            creature->startTurn();
        }
        
    }
    
    log("Starting turn for: %d, %d", _turnNumber, _currentTurnType);
    
    
    
    
    
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
        this->appendMethodToActivity(CALLBACK0_SELECTOR(BattleScene::takeAIMove));
    }
}


void BattleScene::takeAIMove()
{
    // Find AI Creature
    Vector<Creature *> * creatureList = (_currentTurnType == CreatureType_Enemy) ? _battleField->getEnemyList() : _battleField->getNPCList();
    
    Creature * target = nullptr;
    for (Creature * creature : *creatureList) {
        if (!creature->hasTakenAction())
        {
            target = creature;
            break;
        }
    }
    
    if (target != nullptr)
    {
        // Take Move
        RoutePoint * route = new RoutePoint();
        Vec2 position = _battleField->getObjectPosition(target);
        route->appendPoint(Vec2(position.x, position.y + 4));
        route->appendPoint(Vec2(position.x + 5, position.y + 4));
        
        CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, target, route);
        this->_activityQueue->appendActivity(activity);
        
        //
        this->appendMethodToActivity(CALLBACK1_SELECTOR(BattleScene::takeAIAction), target->getId());
    }
    else
    {
        // Start Next Turn
        this->appendMethodToActivity(CALLBACK0_SELECTOR(BattleScene::startTurn));
    }
}
void BattleScene::takeAIAction(int creatureId)
{
    log("Take AI Action. ID = %d", creatureId);
    
    Creature * creature = _battleField->getCreatureById(creatureId);
    
    this->waiveTurn(creature);
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK0 selector)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(this, selector));
    _activityQueue->appendActivity(callback);
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK1 selector, int value)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(this, selector, value));
    _activityQueue->appendActivity(callback);
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK2 selector, Ref* parameter)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(this, selector, parameter));
    _activityQueue->appendActivity(callback);
}

void BattleScene::showMessage(Message * message)
{
    this->_messageLayer->showMessage(message);
}

void BattleScene::testCallMethod(std::function<void(int)> callback)
{
    callback(4);
}

void BattleScene::testCallBack2(Ref* val)
{
    log("Called to here with object.");
}

void BattleScene::testCallBack1(int num)
{
    log("Called to here %d", num);
}

void BattleScene::testCallBack0()
{
    log("Called to here");
}