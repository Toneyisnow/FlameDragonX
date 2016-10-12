//
//  FightScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "CounterScene.hpp"

CounterScene::CounterScene(CounterInfo * info)
{
    _isClosing = false;
    
    _information = info;
    _information->retain();
    
    _layer = Layer::create();
    this->addChild(_layer);
    
    _tickCount = 0;
    schedule(CC_SCHEDULE_SELECTOR(CounterScene::takeTick), 1.0f / Constants::GAME_FPS);
    
    Size winSize = Constants::getScreenSize();
    
    // Add background image
    std::string backgroundImagefile = StringUtils::format("Backgrounds/Background-%02d.png", info->getBackgroundImageId());
    ScaledSprite * backgroundImage = ScaledSprite::create(backgroundImagefile);
    backgroundImage->setScale(1.3f);
    backgroundImage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    _layer->addChild(backgroundImage);
    
    // Add Tai
    std::string taiImageFile = StringUtils::format("Tais/Tai-%02d.png", info->getBackgroundImageId());
    ScaledSprite * taiImage = ScaledSprite::create(taiImageFile);
    taiImage->setScale(1.3f);
    taiImage->setPosition(Vec2(winSize.width * 0.7f, winSize.height * 0.2f));
    _layer->addChild(taiImage);
    
}

CounterScene::~CounterScene()
{
    _information->release();
}

void CounterScene::start()
{
    
}

void CounterScene::takeTick(float dt)
{
    
}

void CounterScene::closeScene()
{
    if (_isClosing) {
        return;
    }
    
    _isClosing = true;
    
    /*
     Add the follwoing code to Scene class:
     
     void Director::popScene(std::function<Scene*(Scene*)> wrappingFunc) {
     popScene();
     if (_nextScene) {
     _nextScene = wrappingFunc(_nextScene);
     }
     }
     */
    auto f = [](Scene* scene) {
        return TransitionFade::create(0.6f, scene);
    };
    Director::getInstance()->popScene(f);
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}
