//
//  EventChapter1.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventChapter1.hpp"
#include "BattleScene.hpp"
#include "BattleField.hpp"
#include "Friend.hpp"
#include "Enemy.hpp"
#include "BatchActivity.hpp"
#include "CreatureMoveActivity.hpp"

void EventChapter1::loadEvents()
{
    this->loadTurnEvent(1, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round1));
    
}

void EventChapter1::round1()
{
    BattleField * field = _battleScene->getBattleField();
    
    field->addCreature(Friend::create(1, 1), Vec2(8, 20));
    field->addCreature(Friend::create(2, 2), Vec2(11, 21));
    field->addCreature(Friend::create(3, 3), Vec2(9, 22));
    field->addCreature(Friend::create(4, 4), Vec2(12, 23));
    
    BatchActivity * batch = new BatchActivity();
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(field, 1);
    activity1->appendPosition(8, 15);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(field, 2);
    activity2->appendPosition(11, 16);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(field, 3);
    activity3->appendPosition(9, 17);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(field, 4);
    activity4->appendPosition(12, 18);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    
    for (int i = 1; i <= 5; i ++)
    {
        showTalkMessage(1, 1, i);
    }
    
    this->appendActivityMethod(CALLBACK0_SELECTOR(EventChapter1::round1_1));
}

void EventChapter1::round1_1()
{
    BattleField * field = _battleScene->getBattleField();
    
    field->addCreature(Enemy::create(11, 50101), Vec2(2, 22));
    field->addCreature(Enemy::create(12, 50101), Vec2(3, 22));
    field->addCreature(Enemy::create(13, 50101), Vec2(4, 23));
    field->addCreature(Enemy::create(14, 50101), Vec2(5, 23));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(field, 11);
    activity1->appendPosition(3, 22);
    activity1->appendPosition(3, 19);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(field, 12);
    activity2->appendPosition(4, 22);
    activity2->appendPosition(4, 19);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(field, 13);
    activity3->appendPosition(4, 20);
    activity3->appendPosition(6, 20);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(field, 14);
    activity4->appendPosition(5, 20);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    
}

