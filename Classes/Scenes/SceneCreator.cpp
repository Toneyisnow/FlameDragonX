//
//  TitleScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#include <stdio.h>

#include "SceneCreator.h"
#include "TitleLayer.hpp"

USING_NS_CC;

Scene* SceneCreator::createTitleScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}





