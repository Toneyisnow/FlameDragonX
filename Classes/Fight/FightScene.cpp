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
    
    if (result->getCounterObject() == nullptr)
    {
        throw new exception();
    }
    
    _subject = result->getCounterObject()->getSubject();
    _target = result->getCounterObject()->getTargetList().at(0);
    
    
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
}

void FightScene::takeTick(float dt)
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
        return TransitionFade::create(1.0f, scene);
    };
    Director::getInstance()->popScene(f);
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}
