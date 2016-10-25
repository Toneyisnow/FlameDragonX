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
#include "GameOverLayer.hpp"
#include "DataStore.hpp"
#include "VillageNormalLayer.hpp"
#include "VillageVacuumLayer.hpp"

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

Scene* SceneCreator::createGameOverScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

Scene* SceneCreator::createVillageScene(ChapterRecord * chapterRecord)
{
    auto scene = Scene::create();
    VillageLayer * layer = nullptr;
    ShopDefinition * shop = DataStore::getInstance()->getShopDefinition(chapterRecord->getChapterId(), ShopType_Amor);
    if (shop != nullptr)
    {
        layer = VillageNormalLayer::create();
    }
    else
    {
        layer = VillageVacuumLayer::create();
    }
    
    layer->loadWithRecord(chapterRecord);
    scene->addChild(layer);
    
    return scene;
}

Scene* SceneCreator::createPickFriendScene(ChapterRecord * chapterRecord)
{
    auto scene = Scene::create();
    
    return scene;
}
