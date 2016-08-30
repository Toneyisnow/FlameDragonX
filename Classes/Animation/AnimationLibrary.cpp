//
//  AnimationLibrary.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "AnimationLibrary.hpp"
#include "Constants.hpp"

AnimationLibrary * AnimationLibrary::_instance = nullptr;

AnimationLibrary * AnimationLibrary::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AnimationLibrary();
    }
    
    return _instance;
}

AnimationLibrary::AnimationLibrary()
{
    _slideAnimationDictionary = new Map<std::string, SlideAnimation*>();
    
}

AnimationLibrary::~AnimationLibrary()
{
    _slideAnimationDictionary->clear();
    delete _slideAnimationDictionary;
}

void AnimationLibrary::loadBattleAnimationsForCreature(int creatureAniId)
{
    // Load Idle Animation
    SlideAnimation *idleAnimation = new SlideAnimation(Constants::TickPerFrame_IdleAnimation, true, true);
    idleAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, 1));
    idleAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, 2));
    idleAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, 3));
    idleAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, 2));
    
    std::string key = StringUtils::format("Idle-%03d", creatureAniId);
    _slideAnimationDictionary->insert(key, idleAnimation);
    idleAnimation->release();
    
    // Load Walk Animation
    this->loadWalkAnimationForCreature(creatureAniId, DirectionLeft, 5);
    this->loadWalkAnimationForCreature(creatureAniId, DirectionUp, 8);
    this->loadWalkAnimationForCreature(creatureAniId, DirectionRight, 11);
    this->loadWalkAnimationForCreature(creatureAniId, DirectionDown, 2);
    
}

void AnimationLibrary::loadWalkAnimationForCreature(int creatureAniId, Direction direction, int centerImageId)
{
    SlideAnimation *walkAnimation = new SlideAnimation(Constants::TickPerFrame_MoveAnimation, true, true);
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId - 1));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId + 1));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId));
    std::string key = StringUtils::format("Walk-%02d-%03d", direction, creatureAniId);
    _slideAnimationDictionary->insert(key, walkAnimation);
    walkAnimation->release();
}

SlideAnimation * AnimationLibrary::getIdleAnimation(int creatureAniId)
{
    std::string key = StringUtils::format("Idle-%03d", creatureAniId);
    return _slideAnimationDictionary->at(key);
}

SlideAnimation * AnimationLibrary::getWalkAnimation(int creatureAniId, Direction direction)
{
    std::string key = StringUtils::format("Walk-%02d-%03d", direction, creatureAniId);
    return _slideAnimationDictionary->at(key);
}

std::string AnimationLibrary::filenameForBattleFieldAnimation(int creatureAniId, int index)
{
    return StringUtils::format("Icons/%03d/Icon-%03d-%02d.png", creatureAniId, creatureAniId, index);
}
