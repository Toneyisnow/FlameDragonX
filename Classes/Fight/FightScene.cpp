//
//  FightingScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "FightScene.hpp"
#include "CallbackMethod.hpp"

FightScene::FightScene(CounterInfo * info, FightResult * result)
: CounterScene(info)
{
    _fightResult = result;
    _fightResult->retain();
    
    _layer = Layer::create();
    this->addChild(_layer);

    schedule(CC_SCHEDULE_SELECTOR(FightScene::takeDeltaTimeTick), 4.0);
    
    
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
}

void FightScene::takeDeltaTimeTick(float dt)
{
    
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
        return TransitionMoveInL::create(1.0f, scene);
    };
    Director::getInstance()->popScene(f);
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}