//
//  MagicScene.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#include "MagicScene.hpp"
#include "AnimationLibrary.hpp"
#include "DataStore.hpp"
#include "MoveByActivity.hpp"
#include "AnimateActivity.hpp"
#include "FightFrame.hpp"


MagicScene::MagicScene(CounterInfo * info, MagicResult * result)
: CounterScene(info)
{
    _magicResult = result;
    _magicResult->retain();
    
    if (result->getCounterObject() == nullptr)
    {
        throw new exception();
    }
    
    _subject = result->getCounterObject()->getSubject();
    _targetList = result->getCounterObject()->getTargetList();
    _targetCount = (int)_targetList.size();
    _magic = DataStore::getInstance()->getMagicDefinition(result->getMagicId());
    
    _subjectSkillAnimation = AnimationLibrary::getInstance()->getFightAnimation(_subject->getDefinition()->animationId, FightAnimationType_Skill);
    _subjectIdleAnimation = AnimationLibrary::getInstance()->getFightAnimation(_subject->getDefinition()->animationId, FightAnimationType_Idle);
    
    
    _firstTargetIdleAnimation = AnimationLibrary::getInstance()->getFightAnimation(_targetList.at(0)->getDefinition()->animationId, FightAnimationType_Idle);
    _lastTargetIdleAnimation = AnimationLibrary::getInstance()->getFightAnimation(_targetList.at(_targetList.size()-1)->getDefinition()->animationId, FightAnimationType_Idle);
    
    _magicAnimation = AnimationLibrary::getInstance()->getMagicAnimation(_magic->getDefinitionId(), (_subject->getType() == CreatureType_Enemy) ? MagicAnimationType_Bad : MagicAnimationType_Good);
    
    _showingMagic = false;
    _switchingTarget = false;
    _switchingTargetTick = true;
    _isMagicTriggered = false;
    _currentTargetIndex = 0;
    
    this->start();
}

MagicScene::~MagicScene()
{
    _magicResult->autorelease();
    _subjectInfo->release();
    _targetInfo->release();
    
}

void MagicScene::start()
{
    Size screenSize = Constants::getScreenSize();
    Vec2 screenCenter = Vec2(screenSize.width / 2, screenSize.height / 2);
    
    // Subject and Target
    
    _subjectSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _subject->getDefinition()->animationId, _subject->getDefinition()->animationId));
    _subjectSprite->setScale(1.3f);
    _subjectSprite->setPosition(screenCenter);
    _layer->addChild(_subjectSprite, (_subject->getType() == CreatureType_Enemy) ? ZORDER_ENEMY : ZORDER_FRIEND);
    
    _targetSprite = ScaledSprite::create(StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", _targetList.at(0)->getDefinition()->animationId, _targetList.at(0)->getDefinition()->animationId));
    _targetSprite->setScale(1.3f);
    _targetSprite->setPosition(screenCenter);
    _layer->addChild(_targetSprite, (_targetList.at(0)->getType() == CreatureType_Enemy) ? ZORDER_ENEMY : ZORDER_FRIEND);
    
    _magicSprite = ScaledSprite::create(StringUtils::format("Fights/003/Fight-003-1-01.png"));
    _magicSprite->setScale(1.3f);
    _magicSprite->setPosition(screenCenter);
    _layer->addChild(_magicSprite, ZORDER_MAGIC);
    
    
    _subjectAnimate = new CombinedActivity();
    _firstTargetAnimate = new CombinedActivity();
    _lastTargetAnimate = new CombinedActivity();
    _magicAnimate =  new AnimateActivity(_magicSprite);
    _magicAnimate->setAnimation(_magicAnimation);
    _magicAnimate->setCallback(this, CALLBACK2_SELECTOR(MagicScene::onMagicHit));
    _switchingAnimate = new CombinedActivity();
    
    // Creature Bar
    _subjectInfo = new CreatureInfoMessage(_subject);
    _subjectInfo->showDialog(_layer);
    _subjectInfo->setZOrder((_subject->getType() == CreatureType_Enemy) ? ZORDER_ENEMYBAR : ZORDER_FRIENDBAR);
    _subjectInfo->setPosition(this->getBarLocation(_subject));
    _subjectInfo->setMp(_subject->creatureData()->mpCurrent + _magic->mpCost());
    
    _targetInfo = new CreatureInfoMessage(_targetList.at(0));
    _targetInfo->showDialog(_layer);
    _targetInfo->setZOrder((_targetList.at(0)->getType() == CreatureType_Enemy) ? ZORDER_ENEMYBAR : ZORDER_FRIENDBAR);
    _targetInfo->setPosition(this->getBarLocation(_targetList.at(0)));
    _targetInfo->setHp(_magicResult->getCounterResult(0)->hpBefore);
    
    // Switching Animate
    MoveByActivity * a1 = MoveByActivity::create(_targetSprite, Vec2(-240, 0), 20);
    MoveByActivity * a2 = MoveByActivity::create(_targetSprite, Vec2(240, 0), 20);
    if (_subject->getType() == CreatureType_Enemy) {
        _switchingAnimate->appendActivity(a2);
        _switchingAnimate->appendActivity(a1);
    } else {
        _switchingAnimate->appendActivity(a1);
        _switchingAnimate->appendActivity(a2);
    }
    
    
    _subjectAnimate->appendActivity(AnimateActivity::create(_subjectSprite, _subjectIdleAnimation));
    _subjectAnimate->appendActivity(AnimateActivity::create(_subjectSprite, _subjectIdleAnimation));
    
    AnimateActivity * animate = AnimateActivity::create(_subjectSprite, _subjectSkillAnimation);
    animate->setCallback(this, CALLBACK2_SELECTOR(MagicScene::onTriggerMagic));
    _subjectAnimate->appendActivity(animate);
    
    while (_firstTargetAnimate->getTotalTick() < _subjectAnimate->getTotalTick()) {
        _firstTargetAnimate->appendActivity(AnimateActivity::create(_targetSprite, _firstTargetIdleAnimation));
    }
    
    _subjectAnimate->appendActivity(AnimateActivity::create(_subjectSprite, _subjectIdleAnimation));
    _subjectAnimate->appendActivity(AnimateActivity::create(_subjectSprite, _subjectIdleAnimation));

    _firstTargetAnimate->appendActivity(AnimateActivity::create(_targetSprite, _lastTargetIdleAnimation));
    _firstTargetAnimate->appendActivity(AnimateActivity::create(_targetSprite, _lastTargetIdleAnimation));
    _lastTargetAnimate->appendActivity(AnimateActivity::create(_targetSprite, _lastTargetIdleAnimation));
    _lastTargetAnimate->appendActivity(AnimateActivity::create(_targetSprite, _lastTargetIdleAnimation));
}

void MagicScene::onTriggerMagic(Ref * frameObj)
{
    // This should only be called once during the animation, that means the Subject Animation
    // should have only one frame with 100 defined
    if (_isMagicTriggered) {
        return;
    }
    
    FightFrame * frame = (FightFrame *)frameObj;
    FightFrameDefinition * frameDefinition = frame->getDefinition();
    if (frameDefinition->isHitting()) {
        
        _isMagicTriggered = true;
        _subjectInfo->setMp(_subject->creatureData()->mpCurrent);
        
        _magicAnimate->reset();
        _showingMagic = true;
    }
}

void MagicScene::takeTick(float dt)
{
    _tickCount ++;
    
    if (_showingMagic) {
        this->tickMagic();
        return;
    }
    
    if (_switchingTarget)
    {
        this->tickSwitching();
        return;
    }
    
    _subjectAnimate->takeTick(_tickCount);
    if (!_isMagicTriggered) {
        _firstTargetAnimate->takeTick(_tickCount);
    } else {
        _lastTargetAnimate->takeTick(_tickCount);
    }
    
    if (_subjectAnimate->hasFinished() && _lastTargetAnimate->hasFinished()) {
        
        closeScene();
    }
}

void MagicScene::tickMagic()
{
    _magicAnimate->takeTick(_tickCount);
    if (_magicAnimate->hasFinished()) {
        
        _showingMagic = false;
        _magicAnimate->reset();
        
        _switchingTarget = (_currentTargetIndex < _targetCount - 1);
    }
}

void MagicScene::tickSwitching()
{
    _switchingAnimate->takeTick(_tickCount);
    
    if (_switchingAnimate->hasFinished()) {
        
        _switchingTarget = false;
        _switchingAnimate->reset();
        _switchingTargetTick = true;
        
        _showingMagic = true;
        return;
    }
    
    if (_switchingAnimate->getCurrentIndex() == 1 && _switchingTargetTick) {
        _switchingTargetTick = false;
        
        _currentTargetIndex ++;
        if (_currentTargetIndex < _targetCount)
        {
            // Update Target Sprite
            int animationId = _targetList.at(_currentTargetIndex)->getDefinition()->animationId;
            std::string filename = StringUtils::format("Fights/%03d/Fight-%03d-1-01.png", animationId, animationId);
            _targetSprite->setTexture(filename);
            
            // Update the Target Bar
            _targetInfo->removeDialog();
            _targetInfo->release();
            
            _targetInfo = new CreatureInfoMessage(_targetList.at(_currentTargetIndex));
            _targetInfo->showDialog(_layer);
            _targetInfo->setZOrder((_targetList.at(_currentTargetIndex)->getType() == CreatureType_Enemy) ? ZORDER_ENEMYBAR : ZORDER_FRIENDBAR);
            _targetInfo->setPosition(this->getBarLocation(_targetList.at(_currentTargetIndex)));
            
            CounterResult * counterResult = _magicResult->getCounterResult(_currentTargetIndex);
            _targetInfo->setHp(counterResult->hpBefore);
        }
    }
}

void MagicScene::onMagicHit(Ref * frameObj)
{
    // Update the HP Value according to the magic
    
    FightFrame * frame = (FightFrame *)frameObj;
    FightFrameDefinition * frameDefinition = frame->getDefinition();
    if (frameDefinition->isHitting()) {
        
        CounterResult * counterResult = _magicResult->getCounterResult(_currentTargetIndex);
        int hpValue = counterResult->hpBefore - (counterResult->hpBefore - counterResult->hpAfter) * frameDefinition->hittingRate();
        
        _targetInfo->setHp(hpValue);
    }
}
