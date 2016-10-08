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

class SceneCreator : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createTitleScene();
    static cocos2d::Scene* createGameOverScene();
    
};

#endif /* TitleScene_h */
