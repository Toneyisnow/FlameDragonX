//
//  VillageLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/24/16.
//
//

#include "VillageLayer.hpp"
#include "SceneCreator.hpp"
#include "BattleScene.hpp"
#include "DataStore.hpp"

void VillageLayer::loadWithRecord(ChapterRecord * record)
{
    this->_chapterRecord = record;
    this->_chapterRecord->retain();
    _chapterId = record->getChapterId();
}

void VillageLayer::doExit()
{
    Scene * scene = nullptr;
    
    if (this->needPickFriend())
    {
        scene = SceneCreator::createPickFriendScene(_chapterRecord);
    }
    else if (this->needAutoPickFriend())
    {
        Vector<FDNumber *> selectedFriends;
        for (CreatureRecord * creatureRecord : _chapterRecord->getFriendRecordList()) {
            selectedFriends.pushBack(FDNumber::numberWithInt(creatureRecord->creatureId));
        }
        
        scene = new BattleScene(_chapterRecord, selectedFriends);
    }
    else
    {
        scene = new BattleScene(_chapterRecord);
    }
    
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
    
}

bool VillageLayer::needPickFriend()
{
    return (_chapterRecord->getFriendRecordList().size() > DataStore::getInstance()->getMaxFriendCount(_chapterId));
}

bool VillageLayer::needAutoPickFriend()
{
    CreatureRecord * creatureRecord = _chapterRecord->getFriendRecordList().at(_chapterRecord->getFriendRecordList().size() - 1);
    
    return (creatureRecord->creatureId > DataStore::getInstance()->getMaxFriendCount(_chapterId));
}


