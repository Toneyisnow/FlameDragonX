//
//  MagicScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "MagicScene.hpp"

MagicScene::MagicScene(CounterInfo * info, MagicResult * result)
: CounterScene(info)
{
    _magicResult = result;
    _magicResult->retain();
    
    _layer = Layer::create();
    this->addChild(_layer);
    
    Sprite * background = Sprite::create(StringUtils::format("Backgrounds/Background-%02d.png", info->getBackgroundImageId()));
    background->setPosition(Vec2(240, 160));
    _layer->addChild(background);
    
    schedule(CC_SCHEDULE_SELECTOR(MagicScene::takeDeltaTimeTick), 3.0);
    
}

MagicScene::~MagicScene()
{
    _magicResult->autorelease();
}

void MagicScene::takeDeltaTimeTick(float dt)
{
    auto f = [](Scene* scene) {
        return TransitionFade::create(1.0f, scene);
    };
    Director::getInstance()->popScene(f);
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}
