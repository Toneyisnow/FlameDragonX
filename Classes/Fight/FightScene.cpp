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
    
    _subjectAnimation = new CombinedAnimation();
    _targetAnimation = new CombinedAnimation();
    
    this->start();
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
    _subjectAnimation->release();
    _targetAnimation->release();
    
    _subjectAnimate->release();
    _targetAnimate->release();
}

void FightScene::start()
{
    Size screenSize = Constants::getScreenSize();
    Vec2 screenCenter = Vec2(screenSize.width / 2, screenSize.height / 2);
    
    
    // Subject and Target
    
    _subjectSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _subject->getDefinition()->animationId, _subject->getDefinition()->animationId));
    _subjectSprite->setScale(1.3f);
    _subjectSprite->setPosition(screenCenter);
    _layer->addChild(_subjectSprite);
    
    _targetSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _target->getDefinition()->animationId, _target->getDefinition()->animationId));
    _targetSprite->setScale(1.3f);
    _targetSprite->setPosition(screenCenter);
    _layer->addChild(_targetSprite);
    
    _subjectAnimate = new FDAnimate(_subjectSprite);
    _subjectAnimate->setAnimation(_subjectAnimation);
    _targetAnimate = new FDAnimate(_targetSprite);
    _targetAnimate->setAnimation(_targetAnimation);
    
    
    // Creature Bar
    _subjectInfo = new CreatureInfoMessage(_subject);
    _subjectInfo->showDialog(_layer);
    _subjectInfo->setPosition(this->getBarLocation(_subject));
    if (_fightResult->fightBackInfo1() != nullptr) {
        CounterResult * back1 = _fightResult->fightBackInfo1();
        //// _subjectInfo->setHp(_fightResult->fightBackInfo1()->hpBefore);
    }
    _subjectInfo->release();
    
    _targetInfo = new CreatureInfoMessage(_target);
    _targetInfo->showDialog(_layer);
    _targetInfo->setHp(_fightResult->attackInfo1()->hpBefore);
    _targetInfo->setPosition(this->getBarLocation(_target));
    _targetInfo->release();
    
    if (_subjectAttackAnimation->isRemoteAttack())
    {
        this->setTargetVisible(false);
    }
    
    _subjectAnimation->appendAnimation(_subjectIdleAnimation);
    _subjectAnimation->appendAnimation(_subjectIdleAnimation);
    
    _subjectAnimation->appendAnimation(_subjectAttackAnimation);
    if (_fightResult->attackInfo2() != nullptr) {
        _subjectAnimation->appendAnimation(_subjectAttackAnimation);
    }
    
    alignSubjectTargetAnimation();
    
    if (_fightResult->fightBackInfo1() != nullptr) {
        _targetAnimation->appendAnimation(_targetAttackAnimation);
    }
    if (_fightResult->fightBackInfo2() != nullptr) {
        _targetAnimation->appendAnimation(_targetAttackAnimation);
    }
    
    alignSubjectTargetAnimation();
    
    _subjectAnimation->appendAnimation(_subjectIdleAnimation);
    _subjectAnimation->appendAnimation(_subjectIdleAnimation);
    alignSubjectTargetAnimation();
    
}

void FightScene::alignSubjectTargetAnimation()
{
    while (_subjectAnimation->getTotalTick() < _targetAnimation->getTotalTick()) {
        _subjectAnimation->appendAnimation(_subjectIdleAnimation);
    }
    while (_targetAnimation->getTotalTick() < _subjectAnimation->getTotalTick()) {
        _targetAnimation->appendAnimation(_targetIdleAnimation);
    }
}

void FightScene::takeTick(float dt)
{
    _tickCount ++;
    
    _subjectAnimate->takeTick(_tickCount);
    _targetAnimate->takeTick(_tickCount);
    
    
    if (_subjectAnimate->hasFinished() && _targetAnimate->hasFinished()) {
        closeScene();
    }
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
