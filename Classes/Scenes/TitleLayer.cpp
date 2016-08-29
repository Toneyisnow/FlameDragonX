//
//  TitleLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#include "TitleLayer.hpp"
#include "ui/CocosGUI.h"
#include "BattleRecord.hpp"
#include "BattleScene.hpp"


USING_NS_CC;

using namespace cocos2d::ui;

// on "init" you need to initialize your instance
bool TitleLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _screen = new FDScreen(this, 320, 200, false);
    
    Sprite* mainSprite = Sprite::create("Title.png");
    _screen->addChild(mainSprite, 160, 100, 1);
    
    
    auto buttonStart = Button::create("Title_Start_1.png", "Title_Start_0.png", "Title_Start_0.png");
    buttonStart->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onStartGame();
                break;
            default:
                break;
        }
    });
    
    _screen->addChild(buttonStart, 70, 25, 1);
    
    auto buttonLoad = Button::create("Title_Load_1.png", "Title_Load_0.png", "Title_Load_0.png");
    buttonLoad->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onLoadGame();
                break;
            default:
                break;
        }
    });
    
    _screen->addChild(buttonLoad, 160, 25, 1);
    
    auto buttonContinue = Button::create("Title_Continue_1.png", "Title_Continue_0.png", "Title_Continue_0.png");
    buttonContinue->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->onContinueGame();
                break;
            default:
                break;
        }
    });
    
    buttonContinue->setEnabled(false);
    
    _screen->addChild(buttonContinue, 250, 25, 1);
    
    
    return true;
}

void TitleLayer::onStartGame()
{
    log("onStartGame");
    
    ChapterRecord * chapterRecord = ChapterRecord::createSample();
    //BattleScene * scene = BattleScene::loadByChapterRecord(chapterRecord);
    BattleScene * scene = new BattleScene(chapterRecord);
    
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
    
    scene->release();
}

void TitleLayer::onLoadGame()
{
    log("onLoadGame");
}

void TitleLayer::onContinueGame()
{
    log("onContinueGame");
}

