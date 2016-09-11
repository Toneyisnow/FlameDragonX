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
    _information = info;
    _information->retain();
}

CounterScene::~CounterScene()
{
    _information->release();
}