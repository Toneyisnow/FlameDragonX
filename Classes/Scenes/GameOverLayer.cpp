//
//  GameOverLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/7/16.
//
//

#include "GameOverLayer.hpp"
#include "Constants.hpp"
#include "ScaledSprite.hpp"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    Size screen = Constants::getScreenSize();
    
    Sprite* mainSprite = ScaledSprite::create("Others/GameOver.png");
    mainSprite->setPosition(screen.width / 2, screen.height / 2);
    mainSprite->setScale(scaleFactor * 1.5f);
    this->addChild(mainSprite);
    
    this->scheduleOnce(schedule_selector(GameOverLayer::closeScene), 3.0f);
    
    return true;
}

void GameOverLayer::closeScene(float dt)
{
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
}
