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
#include "MagicScene.hpp"
#include "LocalizedStrings.hpp"
#include "DurationActivity.hpp"
#include "CompositeBox.hpp"
#include "SceneCreator.h"
#include "ShowMessageActivity.hpp"
#include "ConfirmMessage.hpp"
#include "BatchActivity.hpp"
#include "Enemy.hpp"
#include "LocalizedStrings.hpp"

USING_NS_CC;

BattleScene::BattleScene(ChapterRecord* record)
{
    // DataStore::getInstance()->loadData();
    _chapterId = record->getChapterId();
    
    LocalizedStrings::getInstance()->loadChapterStrings(_chapterId);
    
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
    
    _totalMoney = record->getMoney();
    
    _turnNumber = 0;
    startTurn();
    
    //////// Test Functions
    
    CreatureDefinition * def = DataStore::getInstance()->getCreatureDefinition(3);
    CreatureDefinition * def2 = DataStore::getInstance()->getCreatureDefinition(50508);
    
    LevelUpDefinition * levelup = DataStore::getInstance()->getLevelUpDefinition(1016);
    LevelUpMagicDefinition * levelupmagic = DataStore::getInstance()->getLevelUpMagicDefinition(302, 23);
    OccupationDefinition * occupation = DataStore::getInstance()->getOccupationDefinition(999);
    ShopDefinition * shop = DataStore::getInstance()->getShopDefinition(27, ShopType_Secret);
    TransfersDefinition * transfers = DataStore::getInstance()->getTransfersDefinition(17);
    
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

MessageLayer * BattleScene::getMessageLayer()
{
    return this->_messageLayer;
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
    if (_messageLayer->isActive()) {
        _messageLayer->takeTick(synchronizedTick);
    }
    else
    {
        this->_battleField->takeTick(synchronizedTick);
        this->_activityQueue->takeTick(synchronizedTick);
    }
}

int BattleScene::getTurnNumber()
{
    return _turnNumber;
}

CreatureType BattleScene::getCurrentTurnType()
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
    CounterInfo * info = new CounterInfo(_chapterId, callback);
    FightScene * scene = new FightScene(info, result);
    
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));

    info->release();
    scene->release();
}

void BattleScene::magicTo(Creature * creature, int magicIndex, Vector<Creature *> creatureList)
{
    log("Magic from %d.", creature->getId());
    
    // Calculations on the Attack result
    MagicDefinition * magic = creature->creatureData()->getMagic(magicIndex);
    creature->creatureData()->mpCurrent -= magic->mpCost();
    
    MagicResult * result = GameFormula::dealWithMagic(_battleField, creature, creatureList, magic->getDefinitionId());
    
    // Turn to the magic flight scene
    CallbackMethod * callback = CallbackMethod::create(this, CALLBACK2_SELECTOR(BattleScene::postFightAction), result->getCounterObject());
    CounterInfo * info = new CounterInfo(_chapterId, callback);
    MagicScene * scene = new MagicScene(info, result);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
    
    info->release();
    scene->release();
}

void BattleScene::postFightAction(Ref * counterObjectObj)
{
    log("Enter postFightAction.");
    
    _activityQueue->appendActivity(DurationActivity::create(1.0f));
    
    CounterObject * counterObject = (CounterObject *)counterObjectObj;
    
    Creature * creature = counterObject->getSubject();
    Vector<Creature *> targetList = counterObject->getTargetList();
    
    // Triggered Events
    _eventHandler->notifyTriggeredEvents();
    
    // Analysis Dead Creature and find the drop items
    Vector<FDNumber *> dropItemList;
    
    if (creature->isDead()) {
        CreatureDeadActivity * dead = CreatureDeadActivity::create(this->_battleField, creature);
        _activityQueue->appendActivity(dead);
        
        if (creature->getType() == CreatureType_Enemy) {
            Enemy * enemy = (Enemy *)creature;
            ItemDefinition * dropItem = DataStore::getInstance()->getItemDefinition(enemy->dropItemId);
            if (dropItem != nullptr) {
                dropItemList.pushBack(FDNumber::numberWithInt(dropItem->getDefinitionId()));
            }
        }
    }
    
    BatchActivity * activity = new BatchActivity();
    for (Creature * target : targetList) {
        if (target->isDead()) {
            CreatureDeadActivity * act = CreatureDeadActivity::create(this->_battleField, target);
            activity->addActivity(act);
            
            if (target->getType() == CreatureType_Enemy) {
                Enemy * enemy = (Enemy *)target;
                ItemDefinition * dropItem = DataStore::getInstance()->getItemDefinition(enemy->dropItemId);
                if (dropItem != nullptr) {
                    dropItemList.pushBack(FDNumber::numberWithInt(dropItem->getDefinitionId()));
                }
            }
        }
    }
    _activityQueue->appendActivity(activity);
    activity->release();
    
    
    // Get Talker Friend
    Creature * target = targetList.at(0);
    if (creature->getType() == CreatureType_Friend && !creature->isDead()) {
        _currentTalkerFriend = creature;
    }
    else if (target->getType() == CreatureType_Friend && !target->isDead()) {
        _currentTalkerFriend = target;
    }
    
    if (_currentTalkerFriend != nullptr) {
        
        // Pick up the drop items
        std::string messageTemplate = LocalizedStrings::getInstance()->getMessageString(21);
        
        for (FDNumber * dropItem : dropItemList) {
            ItemDefinition * item = DataStore::getInstance()->getItemDefinition(dropItem->getValue());
            
            // Show Talk Message
            std::string message = StringUtils::format(messageTemplate.c_str(), item->getName().c_str());
            
            TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, _currentTalkerFriend, message);
            _activityQueue->appendActivity(talk);
            
            if (item->isMoney()) {
                _totalMoney += ((MoneyItemDefinition *)item)->quantity();
            }
            else
            {
                if (_currentTalkerFriend->creatureData()->isItemFull()) {
                    
                    // Show Item is Full, ask whether to exchange
                    _currentDropItems.pushBack(FDNumber::numberWithInt(item->getDefinitionId()));
                    
                    ConfirmMessage * itemFull = new ConfirmMessage(_currentTalkerFriend, "Item is Full, Exchange?");
                    itemFull->setReturnFunction(this, CALLBACK1_SELECTOR(BattleScene::confirmItemFullExchange));
                    ShowMessageActivity * showMessage = ShowMessageActivity::create(this, itemFull);
                    _activityQueue->appendActivity(showMessage);
                    itemFull->release();
                }
                else
                {
                    _currentTalkerFriend->creatureData()->addItem(item->getDefinitionId());
                }
            }
        }
        
        // Experience and level up message
        if (_currentTalkerFriend->creatureData()->level < _currentTalkerFriend->getDefinition()->getMaximumLevel()
            && _currentTalkerFriend->lastGainedExperience() > 0) {
            
            std::string experienceMessage = StringUtils::format(LocalizedStrings::getInstance()->getMessageString(5).c_str(), _currentTalkerFriend->lastGainedExperience());
            TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, _currentTalkerFriend, experienceMessage);
            _activityQueue->appendActivity(talk);
            
            std::string levelUpMessage = _currentTalkerFriend->updateExpAndLevelUp();
            if (levelUpMessage.length() > 0)
            {
                TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, _currentTalkerFriend, levelUpMessage);
                _activityQueue->appendActivity(talk);
            }
        }
    }
    
    // Wake up if the AI is idle
    for (Creature * target : targetList) {
        if (target->getType() == CreatureType_Enemy || target->getType() == CreatureType_Npc) {
            AICreature * aiCreature = (AICreature *)target;
            aiCreature->wakeUpByAttack();
        }
    }
    
    // Triggered Events
    this->appendMethodToActivity(_eventHandler, CALLBACK0_SELECTOR(EventHandler::notifyTriggeredEvents));
    
    // End Turn
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);

}

void BattleScene::useItem(Creature * creature, int itemIndex, Creature * target)
{
    // Caculates the effect
    
    
    // Use Animation
    
    // Show Talk messages
    TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, creature, "Test Message");
    _activityQueue->appendActivity(talk);
    
    // End Turn
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);
}

void BattleScene::waiveTurn(Creature * creature)
{
    // Recovery Animation
    
    
    
    // Triggered Events. e.g Position events
    _eventHandler->notifyTriggeredEvents();
    
    // End Turn
    this->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::creatureEndTurn), creature);

}

void BattleScene::waiveAllTurn()
{
    for (Creature * c : *_battleField->getFriendList()) {
        if (!c->hasTakenAction())
        {
            this->waiveTurn(c);
        }
    }
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
        route->appendPoint(Vec2(position.x, position.y + 1));
        route->appendPoint(Vec2(position.x + 1, position.y + 1));
        
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

void BattleScene::confirmItemFullExchange(int result)
{
    if (result == 0) {
        TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, _currentTalkerFriend, "Ok, ignore it");
        _activityQueue->insertActivity(talk);
        
        if (_currentDropItems.size() > 0) {
            _currentDropItems.erase(0);
        }
    }
    else
    {
        CompositeBox * itemBox = new CompositeBox(_currentTalkerFriend, MessageBoxType_Item, MessageBoxOperatingType_Select);
        itemBox->setReturnFunction(this, CALLBACK1_SELECTOR(BattleScene::confirmItemFullExchangeWithItem));
        _messageLayer->showMessage(itemBox);
        itemBox->release();
    }
}

void BattleScene::confirmItemFullExchangeWithItem(int result)
{
    if (result < 0)
    {
        TalkActivity * talk = TalkActivity::create(TalkActivityType_Speak, this, _currentTalkerFriend, "Ok, ignore it");
        _activityQueue->insertActivity(talk);
        
        if (_currentDropItems.size() > 0) {
            _currentDropItems.erase(0);
        }
    }
    else
    {
        // Exchange the item with _currentDropItem
        
        if (_currentDropItems.size() > 0) {
            
            log("Exchange the item with drop item.");
            
            _currentTalkerFriend->creatureData()->removeItem(result);
            _currentTalkerFriend->creatureData()->addItem(_currentDropItems.at(0)->getValue());
            _currentDropItems.erase(0);
        }
    }
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK0 selector)
{
    appendMethodToActivity(this, selector);
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK1 selector, int value)
{
    appendMethodToActivity(this, selector, value);
}

void BattleScene::appendMethodToActivity(SEL_CALLBACK2 selector, Ref* parameter)
{
    appendMethodToActivity(this, selector, parameter);
}

void BattleScene::appendMethodToActivity(Ref* obj, SEL_CALLBACK0 selector)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(obj, selector));
    _activityQueue->appendActivity(callback);
}

void BattleScene::appendMethodToActivity(Ref* obj, SEL_CALLBACK1 selector, int value)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(obj, selector, value));
    _activityQueue->appendActivity(callback);
}

void BattleScene::appendMethodToActivity(Ref* obj, SEL_CALLBACK2 selector, Ref* parameter)
{
    CallbackActivity * callback = CallbackActivity::create(CallbackMethod::create(obj, selector, parameter));
    _activityQueue->appendActivity(callback);
}

void BattleScene::clearAllActivity()
{
    _activityQueue->removeAll();
}

void BattleScene::showMessage(Message * message)
{
    this->_messageLayer->showMessage(message);
}

void BattleScene::showItemStatus(Ref * creatureObj)
{
    Creature * creature = (Creature *)creatureObj;
    if (creature == nullptr)
    {
        return;
    }
    
    CompositeBox * itemBox = new CompositeBox(creature, MessageBoxType_Item, MessageBoxOperatingType_ShowOnly);
    _messageLayer->showMessage(itemBox);
    itemBox->release();
}

void BattleScene::showMagicStatus(Ref * creatureObj)
{
    Creature * creature = (Creature *)creatureObj;
    if (creature == nullptr)
    {
        return;
    }
    
    CompositeBox * magicBox = new CompositeBox(creature, MessageBoxType_Magic, MessageBoxOperatingType_ShowOnly);
    _messageLayer->showMessage(magicBox);
    magicBox->release();
}

void BattleScene::gameWin()
{
    log("Game Win.");
    
    // Switch to VillageScene
}

void BattleScene::gameOver()
{
    log("Game Over");
    
    this->clearAllActivity();
    
    // Switch to GameOverScene
    Scene * gameOverScene = SceneCreator::createGameOverScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, gameOverScene));
}

void BattleScene::gameCleared()
{
    // Stop Background Music
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
