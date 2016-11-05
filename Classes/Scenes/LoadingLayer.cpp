//
//  LoadingLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "LoadingLayer.hpp"
#include "ScaledSprite.hpp"
#include "Constants.hpp"
#include "ChapterRecord.hpp"
#include "SceneCreator.hpp"


// on "init" you need to initialize your instance
bool LoadingLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    Size screen = Constants::getScreenSize();
    
    Sprite* mainSprite = ScaledSprite::create("Others/MessageBox.png");
    mainSprite->setPosition(screen.width / 2, screen.height / 2);
    mainSprite->setScale(scaleFactor * 1.5f);
    this->addChild(mainSprite);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(LoadingLayer::onClicked, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool LoadingLayer::onClicked(Touch* touch, Event* event)
{
    ChapterRecord * chapterRecord = ChapterRecord::createSample();
    Scene * scene = SceneCreator::createVillageScene(chapterRecord);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
    
    return true;
}
