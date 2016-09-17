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
#include "BatchActivity.hpp"
#include "CreatureMoveActivity.hpp"

void EventChapter1::loadEvents()
{
    this->loadTurnEvent(1, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round1));
}

void EventChapter1::round1()
{
    BattleField * field = _battleScene->getBattleField();
    
    Friend * friend1 = new Friend();
    friend1->initWithDefinition(1, 1);
    field->addCreature(friend1, Vec2(8, 20));
    friend1->release();
    
    Friend * friend2 = new Friend();
    friend2->initWithDefinition(2, 2);
    field->addCreature(friend2, Vec2(11, 21));
    friend2->release();
    
    Friend * friend3 = new Friend();
    friend3->initWithDefinition(3, 3);
    field->addCreature(friend3, Vec2(9, 22));
    friend3->release();
    
    Friend * friend4 = new Friend();
    friend4->initWithDefinition(4, 4);
    field->addCreature(friend4, Vec2(12, 23));
    friend4->release();
    
    BatchActivity * batch = new BatchActivity();
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(field, friend1);
    activity1->appendPosition(8, 15);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(field, friend2);
    activity2->appendPosition(11, 16);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(field, friend3);
    activity3->appendPosition(9, 17);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(field, friend4);
    activity4->appendPosition(12, 18);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    
    for (int i = 1; i <= 5; i ++)
    {
        showTalkMessage(1, 1, i);
    }
    
}