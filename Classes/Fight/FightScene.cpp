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
#include "FightFrame.hpp"

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
    
    
    this->start();
}

FightScene::~FightScene()
{
    _fightResult->autorelease();
    
    _subjectAnimate->release();
    _targetAnimate->release();
    
    _subjectInfo->release();
    _targetInfo->release();
}

void FightScene::start()
{
    Size screenSize = Constants::getScreenSize();
    Vec2 screenCenter = Vec2(screenSize.width / 2, screenSize.height / 2);
    
    
    // Subject and Target
    
    _subjectSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _subject->getDefinition()->animationId, _subject->getDefinition()->animationId));
    _subjectSprite->setScale(1.3f);
    _subjectSprite->setPosition(screenCenter);
    _layer->addChild(_subjectSprite, (_subject->getType() == CreatureType_Enemy) ? ZORDER_ENEMY : ZORDER_FRIEND);
    
    _targetSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _target->getDefinition()->animationId, _target->getDefinition()->animationId));
    _targetSprite->setScale(1.3f);
    _targetSprite->setPosition(screenCenter);
    _layer->addChild(_targetSprite, (_target->getType() == CreatureType_Enemy) ? ZORDER_ENEMY : ZORDER_FRIEND);
    
    _subjectAnimate = new CombinedAnimate(_subjectSprite);
    _targetAnimate = new CombinedAnimate(_targetSprite);
    
    
    // Creature Bar
    _subjectInfo = new CreatureInfoMessage(_subject);
    _subjectInfo->showDialog(_layer);
    _subjectInfo->setZOrder((_subject->getType() == CreatureType_Enemy) ? ZORDER_ENEMYBAR : ZORDER_FRIENDBAR);
    _subjectInfo->setPosition(this->getBarLocation(_subject));
    if (_fightResult->fightBackInfo1() != nullptr) {
        CounterResult * back1 = _fightResult->fightBackInfo1();
        //// _subjectInfo->setHp(_fightResult->fightBackInfo1()->hpBefore);
    }
    
    _targetInfo = new CreatureInfoMessage(_target);
    _targetInfo->showDialog(_layer);
    _targetInfo->setZOrder((_target->getType() == CreatureType_Enemy) ? ZORDER_ENEMYBAR : ZORDER_FRIENDBAR);
    _targetInfo->setHp(_fightResult->attackInfo1()->hpBefore);
    _targetInfo->setPosition(this->getBarLocation(_target));
    
    if (_subjectAttackAnimation->isRemoteAttack())
    {
        this->setTargetVisible(false);
    }
    
    _subjectAnimate->appendAnimate(FDAnimate::create(_subjectSprite, _subjectIdleAnimation));
    _subjectAnimate->appendAnimate(FDAnimate::create(_subjectSprite, _subjectIdleAnimation));
    
    _subjectAnimate->appendAnimate(generateAttackAnimate(_subjectSprite, _subjectAttackAnimation, 1, CALLBACK2_SELECTOR(FightScene::onSubjectAttack)));
    
    if (_fightResult->attackInfo2() != nullptr) {
        _subjectAnimate->appendAnimate(generateAttackAnimate(_subjectSprite, _subjectAttackAnimation, 2, CALLBACK2_SELECTOR(FightScene::onSubjectAttack)));
    }
    
    alignSubjectTargetAnimation();
    
    if (_fightResult->fightBackInfo1() != nullptr) {
        _targetAnimate->appendAnimate(generateAttackAnimate(_targetSprite, _targetAttackAnimation, 1, CALLBACK2_SELECTOR(FightScene::onTargetAttack)));
    }
    if (_fightResult->fightBackInfo2() != nullptr) {
        _targetAnimate->appendAnimate(generateAttackAnimate(_targetSprite, _targetAttackAnimation, 2, CALLBACK2_SELECTOR(FightScene::onTargetAttack)));
    }
    
    alignSubjectTargetAnimation();
    
    _targetAnimate->appendAnimate(FDAnimate::create(_targetSprite, _targetIdleAnimation));
    _targetAnimate->appendAnimate(FDAnimate::create(_targetSprite, _targetIdleAnimation));
    alignSubjectTargetAnimation();
}

void FightScene::alignSubjectTargetAnimation()
{
    if (!_subjectAttackAnimation->isRemoteAttack()) {
        while (_subjectAnimate->getTotalTick() < _targetAnimate->getTotalTick()) {
            _subjectAnimate->appendAnimate(FDAnimate::create(_subjectSprite, _subjectIdleAnimation));
        }
    }
    
    while (_targetAnimate->getTotalTick() < _subjectAnimate->getTotalTick()) {
        _targetAnimate->appendAnimate(FDAnimate::create(_targetSprite, _targetIdleAnimation));
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



FDAnimate * FightScene::generateAttackAnimate(Sprite * sprite, SlideAnimation * animation, int tag, SEL_CALLBACK2 onAttack)
{
    FDAnimate * animate = FDAnimate::create(sprite, animation);
    animate->setTag(tag);
    animate->setCallback(this, onAttack);
    
    return animate;
}

void FightScene::onSubjectAttack(Ref * frameObj)
{
    FightFrame * frame = (FightFrame *)frameObj;
    FightFrameDefinition * frameDefinition = frame->getDefinition();
    
    int tag = _subjectAnimate->getCurrentAnimate()->getTag();
    CounterResult * attackInfo = (tag == 2) ? _fightResult->attackInfo2() : _fightResult->attackInfo1();
    
    if (_subjectAttackAnimation->isRemoteAttack())
    {
        if (frameDefinition->isRemote()) {
            this->setTargetVisible(false);
            _subjectInfo->appear();
        } else {
            this->setTargetVisible(true);
            _subjectInfo->hide();
        }
    }
    
    if (frameDefinition->isHitting()) {
        
        int nowValue = attackInfo->hpBefore - (attackInfo->hpBefore - attackInfo->hpAfter) * frameDefinition->hittingRate();
        if (nowValue < 0) {
            nowValue = 0;
        }
        
        _targetInfo->setHp(nowValue);
        
        if (attackInfo->isCriticalHit) {
            // TODO
        }
    }
}

void FightScene::onTargetAttack(Ref * frameObj)
{
    FightFrame * frame = (FightFrame *)frameObj;
    FightFrameDefinition * frameDefinition = frame->getDefinition();
    
    int tag = _subjectAnimate->getCurrentAnimate()->getTag();
    CounterResult * attackInfo = (tag == 2) ? _fightResult->fightBackInfo2() : _fightResult->fightBackInfo1();
    
    if (frameDefinition->isHitting()) {
        
        int nowValue = attackInfo->hpBefore - (attackInfo->hpBefore - attackInfo->hpAfter) * frameDefinition->hittingRate();
        if (nowValue < 0) {
            nowValue = 0;
        }
        
        _subjectInfo->setHp(nowValue);
        
        if (attackInfo->isCriticalHit) {
            // TODO
        }
    }
}

