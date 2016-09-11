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

    schedule(CC_SCHEDULE_SELECTOR(FightScene::takeDeltaTimeTck), 4.0);
    
    
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
}

void FightScene::takeDeltaTimeTck(float dt)
{
    Director::getInstance()->popScene();
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}