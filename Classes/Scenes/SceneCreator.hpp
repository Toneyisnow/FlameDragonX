//
//  TitleScene.h
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#ifndef TitleScene_h
#define TitleScene_h

#include "cocos2d.h"
#include "TitleLayer.hpp"
#include "ChapterRecord.hpp"

USING_NS_CC;

class SceneCreator : public cocos2d::Scene
{
public:
    static Scene* createTitleScene();
    static Scene* createGameOverScene();
    static Scene* createVillageScene(ChapterRecord * chapterRecord);
    static Scene* createPickFriendScene(ChapterRecord * chapterRecord);
};

#endif /* TitleScene_h */
