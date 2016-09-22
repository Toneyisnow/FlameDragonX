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
    
    
    
    
    auto size = Director::getInstance()->getWinSize();
    auto sizein = Director::getInstance()->getWinSizeInPixels();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto designSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    
    Size screen = Constants::getScreenSize();
    
    Sprite* mainSprite = Sprite::create("Title.png");
    mainSprite->setPosition(screen.width / 2, screen.height / 2);
    mainSprite->setScale(scaleFactor * 1.5f);
    this->addChild(mainSprite);
    
    /*
    mainSprite->setScale(scaleFactor * 1.5f);
    mainSprite->setPosition(Vec2(240, 160));
    this->addChild(mainSprite, 1);
    */
    
    _screen = new FDScreen(this);
    // _screen->addToWindow(mainSprite, Vec2(240, 160), 1.0f, 1);
    
    
    //Sprite* mainSprite = Sprite::create("Title.png");
    //_screen->addChild(mainSprite, 160, 100, 1);
    
    
    ///auto buttonStart = Button::create("Title_Start_1.png", "Title_Start_0.png", "Title_Start_0.png");
    ///buttonStart->setPosition(Vec2(240, 120));
    ///this->addChild(buttonStart, 1);
    
    float locationY = MAX(screen.height - Constants::ORIGIN_SCREEN_HEIGHT, 0) + 25;
    
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

    _screen->addToVisible(buttonStart, Vec2(100, locationY), 1.5f, 10);
    
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
    _screen->addToVisible(buttonLoad, Vec2(240, locationY), 1.5f, 10);
    
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
    _screen->addToVisible(buttonContinue, Vec2(380, locationY), 1.5f, 10);
    
    
    return true;
}

void TitleLayer::onStartGame()
{
    log("onStartGame");
    
    // ChapterRecord * chapterRecord = ChapterRecord::createSample();
    
    ChapterRecord * chapterRecord = ChapterRecord::newGame();
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

