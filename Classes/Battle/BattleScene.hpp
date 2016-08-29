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

class BattleScene : public cocos2d::Scene
{
    
private:
    
    int _synchronizedTickCount;
    
    BattleField *_battleField;
    
    
    ActivityQueue * _activityQueue;
    
    
    
    void takeDeltaTimeTck(float dt);
    void takeTick(int synchronizedTick);
    
public:
    
    BattleScene(ChapterRecord * chapterRecord);
    BattleScene(BattleRecord * battleRecord);
    ~BattleScene();
    
    
    BattleField * getBattleField();
    ActivityQueue * getActivityQueue();
    
    // static BattleScene* loadByChapterRecord(ChapterRecord* record);
    // static BattleScene* loadByBattleRecord(BattleRecord* record);
    
    // BattleScene();
    
};

#endif /* BattleScene_hpp */
