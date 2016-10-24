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
#include "Npc.hpp"
#include "BatchActivity.hpp"
#include "CreatureMoveActivity.hpp"
#include "DurationActivity.hpp"

void EventChapter1::loadEvents()
{
    this->loadTurnEvent(1, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::test));
    
    this->loadTurnEvent(3, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round3));
    this->loadTurnEvent(4, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round4));
    this->loadTurnEvent(5, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round5_Boss));
    this->loadTurnEvent(6, CreatureType_Friend, CALLBACK0_SELECTOR(EventChapter1::round6_Npc));
    
    this->loadDieEvent(1, CALLBACK0_SELECTOR(EventLoader::gameOver));
    this->loadDieEvent(5, CALLBACK0_SELECTOR(EventChapter1::hanuoDie));
    this->loadDieEvent(6, CALLBACK0_SELECTOR(EventChapter1::hawateDie));
    
    this->loadDyingEvent(29, CALLBACK0_SELECTOR(EventChapter1::bossDying));
    this->loadTeamEvent(CreatureType_Enemy, CALLBACK0_SELECTOR(EventChapter1::enemyClear));
}

void EventChapter1::test()
{
    Creature * f3 = Friend::create(2, 2);
    f3->creatureData()->hpMax = 999;
    f3->creatureData()->hpCurrent = 999;
    
    _battleField->addCreature(f3, Vec2(7, 23));
    //_battleField->addCreature(Friend::create(2, 2), Vec2(6, 21));
    //_battleField->addCreature(Friend::create(3, 3), Vec2(9, 22));
    //_battleField->addCreature(Friend::create(4, 4), Vec2(12, 23));
    //_battleField->addCreature(Friend::create(6, 6), Vec2(10, 23));
    
    Enemy * a = Enemy::create(11, 50101, 101);
    a->creatureData()->hpCurrent = 1;
    _battleField->addCreature(a, Vec2(4, 18));
    
    _battleField->addCreature(Enemy::create(12, 50101, 101), Vec2(3, 19));
    _battleField->addCreature(Enemy::create(13, 50101, 101), Vec2(4, 20));
    
    Enemy * d = Enemy::create(14, 50101, 101);
    d->creatureData()->hpCurrent = 1;
    _battleField->addCreature(d, Vec2(4, 15));
}

void EventChapter1::round1()
{
    log("Event round1 triggered.");
    
    _battleField->addCreature(Friend::create(1, 1), Vec2(8, 20));
    _battleField->addCreature(Friend::create(2, 2), Vec2(11, 21));
    _battleField->addCreature(Friend::create(3, 3), Vec2(9, 22));
    _battleField->addCreature(Friend::create(4, 4), Vec2(12, 23));
    
    BatchActivity * batch = new BatchActivity();
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 1);
    activity1->appendPosition(8, 15);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 2);
    activity2->appendPosition(11, 16);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 3);
    activity3->appendPosition(9, 17);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 4);
    activity4->appendPosition(12, 18);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    _battleScene->getActivityQueue()->appendActivity(DurationActivity::create(0.8f));
    
    
    showTalkMessage(1, 1, 1, 5);
    
    
    this->appendActivityMethod(CALLBACK0_SELECTOR(EventChapter1::round1_1));
}

void EventChapter1::round1_1()
{
    _battleField->setCursorTo(Vec2(8, 15));
    
    _battleField->addCreature(Enemy::create(11, 50101), Vec2(2, 22));
    _battleField->addCreature(Enemy::create(12, 50101, 101), Vec2(3, 22));
    _battleField->addCreature(Enemy::create(13, 50101), Vec2(4, 23));
    _battleField->addCreature(Enemy::create(14, 50101), Vec2(5, 23));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 11);
    activity1->appendPosition(3, 22);
    activity1->appendPosition(3, 19);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 12);
    activity2->appendPosition(4, 22);
    activity2->appendPosition(4, 19);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 13);
    activity3->appendPosition(4, 20);
    activity3->appendPosition(6, 20);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 14);
    activity4->appendPosition(5, 20);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    _battleScene->getActivityQueue()->appendActivity(DurationActivity::create(0.2f));
    
    this->appendActivityMethod(CALLBACK0_SELECTOR(EventChapter1::round1_2));

}

void EventChapter1::round1_2()
{
    _battleField->setCursorTo(Vec2(3, 3));
    
    _battleField->addCreature(Enemy::create(15, 50101, 101), Vec2(4, 2));
    _battleField->addCreature(Enemy::create(16, 50101),      Vec2(3, 2));
    _battleField->addCreature(Enemy::create(17, 50101, 101), Vec2(2, 3));
    _battleField->addCreature(Enemy::create(18, 50101),      Vec2(2, 3));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 15);
    activity1->appendPosition(7, 2);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 16);
    activity2->appendPosition(3, 3);
    activity2->appendPosition(5, 3);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 17);
    activity3->appendPosition(3, 3);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 18);
    activity4->appendPosition(2, 5);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    batch->release();
    
    _battleScene->getActivityQueue()->appendActivity(DurationActivity::create(0.5f));
    
    _battleScene->appendMethodToActivity(_battleField, CALLBACK2_SELECTOR(BattleField::setCursorObjectTo), FDPoint::create(5, 20));
    
    for (int i = 6; i <= 7; i ++)
    {
        showTalkMessage(1, 1, i);
    }
    
    this->appendActivityMethod(CALLBACK0_SELECTOR(EventChapter1::round1_3));
    
}

void EventChapter1::round1_3()
{
    Creature * enemy = _battleField->getCreatureById(14);
    CreatureMoveActivity * enemyGo = new CreatureMoveActivity(_battleField, enemy);
    enemyGo->appendPosition(8, 20);
    enemyGo->appendPosition(8, 24);
    _battleScene->getActivityQueue()->appendActivity(enemyGo);
    enemyGo->release();
    
    _battleScene->appendMethodToActivity(this, CALLBACK2_SELECTOR(EventLoader::BattleField_RemoveObject), enemy);
    
    _battleScene->appendMethodToActivity(_battleField, CALLBACK2_SELECTOR(BattleField::setCursorObjectTo), FDPoint::create(8, 15));
    
    showTalkMessage(1, 1, 8, 19);
    
}

void EventChapter1::round3()
{
    log("Event round3 triggered.");
    _battleField->addCreature(Friend::create(5, 5), Vec2(12, 12));
    _battleField->addCreature(Friend::create(6, 1016), Vec2(12, 12));
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 5);
    activity1->appendPosition(12, 14);
    _battleScene->getActivityQueue()->appendActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 6);
    activity2->appendPosition(12, 13);
    _battleScene->getActivityQueue()->appendActivity(activity2);
    activity2->release();
    
    
    showTalkMessage(1, 2, 1, 13);
    
}

void EventChapter1::round4()
{
    log("Event round4 triggered.");

    _battleField->setCursorTo(Vec2(23, 23));
    
    _battleField->addCreature(Enemy::create(21, 50101), Vec2(19, 23));
    _battleField->addCreature(Enemy::create(22, 50101, 101), Vec2(20, 22));
    _battleField->addCreature(Enemy::create(23, 50101), Vec2(21, 21));
    _battleField->addCreature(Enemy::create(24, 50101, 801), Vec2(22, 21));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 21);
    activity1->appendPosition(17, 23);
    activity1->appendPosition(17, 21);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 22);
    activity2->appendPosition(20, 20);
    activity2->appendPosition(18, 20);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 23);
    activity3->appendPosition(21, 20);
    activity3->appendPosition(20, 20);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 24);
    activity4->appendPosition(21, 21);
    activity4->appendPosition(21, 19);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    batch->release();

    showTalkMessage(1, 3, 1, 2);
}

void EventChapter1::round5_Boss()
{
    log("Event round5 triggered.");

    _battleField->addCreature(Enemy::create(25, 50101), Vec2(1, 24));
    _battleField->addCreature(Enemy::create(26, 50101), Vec2(2, 24));
    _battleField->addCreature(Enemy::create(27, 50101), Vec2(5, 24));
    _battleField->addCreature(Enemy::create(28, 50101), Vec2(5, 24));
    _battleField->addCreature(Enemy::create(29, 50102, 201), Vec2(4, 23));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 25);
    activity1->appendPosition(1, 21);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 26);
    activity2->appendPosition(2, 21);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 27);
    activity3->appendPosition(5, 23);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 28);
    activity4->appendPosition(6, 24);
    batch->addActivity(activity4);
    activity4->release();
    CreatureMoveActivity * activity5 = new CreatureMoveActivity(_battleField, 29);
    activity5->appendPosition(4, 22);
    batch->addActivity(activity5);
    activity5->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    batch->release();

    showTalkMessage(1, 4, 1, 11);
    
}

void EventChapter1::round6_Npc()
{
    _battleField->addCreature(Npc::create(31, 50103), Vec2(24, 15));
    _battleField->addCreature(Npc::create(32, 50103), Vec2(24, 15));
    _battleField->addCreature(Npc::create(33, 50103), Vec2(24, 15));
    _battleField->addCreature(Npc::create(34, 50103), Vec2(24, 15));
    
    BatchActivity * batch = new BatchActivity();
    
    CreatureMoveActivity * activity1 = new CreatureMoveActivity(_battleField, 31);
    activity1->appendPosition(18, 15);
    batch->addActivity(activity1);
    activity1->release();
    CreatureMoveActivity * activity2 = new CreatureMoveActivity(_battleField, 32);
    activity2->appendPosition(19, 15);
    activity2->appendPosition(19, 14);
    batch->addActivity(activity2);
    activity2->release();
    CreatureMoveActivity * activity3 = new CreatureMoveActivity(_battleField, 33);
    activity3->appendPosition(19, 15);
    activity3->appendPosition(19, 16);
    batch->addActivity(activity3);
    activity3->release();
    CreatureMoveActivity * activity4 = new CreatureMoveActivity(_battleField, 34);
    activity4->appendPosition(19, 15);
    activity4->appendPosition(20, 15);
    batch->addActivity(activity4);
    activity4->release();
    
    _battleScene->getActivityQueue()->appendActivity(batch);
    batch->release();

    showTalkMessage(1, 5, 1, 6);
}

void EventChapter1::bossDying()
{
    showTalkMessage(1, 99, 1);
}

void EventChapter1::hanuoDie()
{
    // Hawate change to NPC
    Creature * hawate = _battleField->getCreatureById(6);
    if (hawate != nullptr)
    {
        showTalkMessage(1, 6, 1, 4);
        
        _battleField->getNPCList()->pushBack(hawate);
        _battleField->getFriendList()->eraseObject(hawate);
        
        hawate->changeCreatureType(CreatureType_Npc);
    }
}

void EventChapter1::hawateDie()
{
    
}

void EventChapter1::enemyClear()
{
    _battleScene->gameCleared();
    
    Creature * hawate = _battleField->getCreatureById(6);
    if (hawate != nullptr)
    {
        _battleField->getFriendList()->eraseObject(hawate);
    }
    
    Creature * hanuo = _battleField->getDeadCreatureById(5);
    if (hanuo != nullptr) {
        _battleField->getFriendList()->pushBack(hawate);
        _battleField->getDeadCreatureList()->eraseObject(hawate);
    }
    
    showTalkMessage(1, 7, 1, 13);
    
    _battleScene->appendMethodToActivity(CALLBACK0_SELECTOR(BattleScene::gameWin));
}
