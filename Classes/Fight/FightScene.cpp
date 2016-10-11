//
//  FightingScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "FightScene.hpp"
#include "CallbackMethod.hpp"
#include "AnimationLibrary.hpp"

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
    
    _subjectAttackAnimation = AnimationLibrary::getInstance()->getFightAnimation(_subject->getDefinition()->animationId, FightAnimationType_Attack);
    _subjectIdleAnimation = AnimationLibrary::getInstance()->getFightAnimation(_subject->getDefinition()->animationId, FightAnimationType_Idle);
    _targetAttackAnimation = AnimationLibrary::getInstance()->getFightAnimation(_target->getDefinition()->animationId, FightAnimationType_Attack);
    _targetIdleAnimation = AnimationLibrary::getInstance()->getFightAnimation(_target->getDefinition()->animationId, FightAnimationType_Idle);
    
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
}

void FightScene::start()
{
    Size screenSize = Constants::getScreenSize();
    Vec2 screenCenter = Vec2(screenSize.width / 2, screenSize.height / 2);
    
    
    // Subject and Target
    _subjectSprite = ScaledSprite::create("Others/Empty.png");
    _subjectSprite->setScale(1.3f);
    _subjectSprite->setPosition(screenCenter);
    _layer->addChild(_subjectSprite);
    
    _targetSprite = ScaledSprite::create("Others/Empty.png");
    _targetSprite->setScale(1.3f);
    _targetSprite->setPosition(screenCenter);
    _layer->addChild(_targetSprite);
    
    // Creature Bar
    _subjectInfo = new CreatureInfoMessage(_subject);
    if (_fightResult->fightBackInfo1() != nullptr) {
        _subjectInfo->setHp(_fightResult->fightBackInfo1()->hpBefore);
    }
    
    _subjectInfo->setPosition(this->getBarLocation(_subject));
    _subjectInfo->showDialog(_layer);
    
    _targetInfo = new CreatureInfoMessage(_target);
    _targetInfo->setHp(_fightResult->attackInfo1()->hpBefore);
    _targetInfo->setPosition(this->getBarLocation(_target));
    _targetInfo->showDialog(_layer);
    
    if (_subjectAttackAnimation->isRemoteAttack())
    {
        this->setTargetVisible(false);
    }
}

void FightScene::takeTick(float dt)
{
    _tickCount ++;
    
    if (_tickCount < 120) {
        return;
    }
    
    /*
     Add the follwoing code to Scene class:
     
     void Director::popScene(std::function<Scene*(Scene*)> wrappingFunc) {
     popScene();
     if (_nextScene) {
     _nextScene = wrappingFunc(_nextScene);
     }
     }
     
     */
    
    if (_tickCount > 120)
    {
        return;
    }
    
    auto f = [](Scene* scene) {
        return TransitionFade::create(1.0f, scene);
    };
    Director::getInstance()->popScene(f);
    
    CallbackMethod * method = _information->getCallback();
    method->execute();
}

void FightScene::setTargetVisible(bool val)
{
    _targetSprite->setVisible(val);
    
    if (val) {
        _targetInfo->appear();
    } else {
        _targetInfo->hide();
    }
    
    if (_target->getType() == CreatureType_Enemy) {
        _taiSprite->setVisible(!val);
    } else {
        _taiSprite->setVisible(val);
    }
}

Vec2 FightScene::getBarLocation(Creature * creature)
{
    Size screenSize = Constants::getScreenSize();
    if (creature->getType() == CreatureType_Friend || creature->getType() == CreatureType_Npc) {
        return Vec2(screenSize.width * 0.7, screenSize.height * 0.85);
    }
    else {
        return Vec2(screenSize.width * 0.25, screenSize.height * 0.1);
    }
}
