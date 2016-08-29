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

USING_NS_CC;

BattleScene::BattleScene(ChapterRecord* record)
{
    // Load Resources
    AnimationLibrary::getInstance()->loadBattleAnimationsForCreature(1);
    AnimationLibrary::getInstance()->loadBattleAnimationsForCreature(2);
    
    
    _activityQueue = new ActivityQueue();
    
    _battleField = new BattleField(this, record->getChapterId());
    
    // add layer as a child to scene
    this->addChild(_battleField);
    
    //layer->initWithChapter(record->getChapterId());
    
    
    
    _synchronizedTickCount = 0;
    schedule(CC_SCHEDULE_SELECTOR(BattleScene::takeDeltaTimeTck), 0.02f);
    
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

