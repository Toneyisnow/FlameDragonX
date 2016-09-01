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

USING_NS_CC;

BattleScene::BattleScene(ChapterRecord* record)
{
    // Load Resources
    AnimationLibrary::getInstance()->preloadBattleAnimationsForCreature(1);
    AnimationLibrary::getInstance()->preloadBattleAnimationsForCreature(2);
    
    DataStore::getInstance()->loadData();
    CreatureDefinition * def = DataStore::getInstance()->getCreatureDefinition(3);
    CreatureDefinition * def2 = DataStore::getInstance()->getCreatureDefinition(50508);
    
    MoneyItemDefinition * item = (MoneyItemDefinition *)DataStore::getInstance()->getItemDefinition(901);
    
    log("Definition of 50508: Ani=%d EX=%d", def2->animationId, def2->initialEX);
    
    //// UserDefault::getInstance()->setIntegerForKey(<#const char *key#>, <#int value#>)
   
    
    _activityQueue = new ActivityQueue();
    
    _battleField = new BattleField(this, record->getChapterId());
    
    // add layer as a child to scene
    this->addChild(_battleField);
    
    //layer->initWithChapter(record->getChapterId());
    
    
    
    _synchronizedTickCount = 0;
    schedule(CC_SCHEDULE_SELECTOR(BattleScene::takeDeltaTimeTck), 1.0 / Constants::GAME_FPS);
    
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

