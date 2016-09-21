//
//  AnimationLibrary.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "AnimationLibrary.hpp"
#include "Constants.hpp"
#include "TransparencyFrame.hpp"
#include "TextureComposer.hpp"

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

void AnimationLibrary::preloadBattleAnimationsForCreature(int creatureAniId)
{
    this->loadIdleAnimation(creatureAniId, false);
    this->loadIdleAnimation(creatureAniId, true);
    
    
    // Load Walk Animation
    this->loadWalkAnimation(creatureAniId, DirectionLeft);
    this->loadWalkAnimation(creatureAniId, DirectionUp);
    this->loadWalkAnimation(creatureAniId, DirectionRight);
    this->loadWalkAnimation(creatureAniId, DirectionDown);
}

void AnimationLibrary::loadIdleAnimation(int creatureAniId, bool greyout)
{
    // Load Idle Animation
    SlideAnimation *idleAnimation = new SlideAnimation(Constants::TickPerFrame_IdleAnimation, true, true);
	
	int indexes[] = {1, 2, 3, 2};
	
	if (!greyout)
	{
		for (int i = 0; i < 4; i++)
		{
			idleAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, indexes[i]));
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			Texture2D * texture = TextureComposer::composeGreyoutTexture(filenameForBattleFieldAnimation(creatureAniId, indexes[i]));
			idleAnimation->appendFrame(texture);
		}
	}
	
	
    std::string key = StringUtils::format("Idle-%03d-%d", creatureAniId, greyout);
    _slideAnimationDictionary->insert(key, idleAnimation);
    idleAnimation->release();
}

void AnimationLibrary::loadDeadAnimation(int creatureAniId)
{
    SlideAnimation *animation = new SlideAnimation(Constants::TickPerFrame_MoveAnimation, false, false);
    
    int indexes[] = {2, 5, 8, 11};
    
    for (int m = 0; m < 3; m ++) {
    
        for (int i = 0; i < 4; i++)
        {
            animation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, indexes[i]));
        }
    }
    
    for (int i = 1; i <= 8; i++) {
        animation->appendFrame(StringUtils::format("Animations/Explode/Explode-%02d.png", i));
    }
    
    std::string key = StringUtils::format("Dead-%03d", creatureAniId);
    _slideAnimationDictionary->insert(key, animation);
    animation->release();
}

void AnimationLibrary::loadWalkAnimation(int creatureAniId, Direction direction)
{
    int centerImageId;
    switch (direction) {
        case DirectionLeft:
            centerImageId = 5;
            break;
        case DirectionUp:
            centerImageId = 8;
            break;
        case DirectionRight:
            centerImageId = 11;
            break;
        case DirectionDown:
            centerImageId = 2;
            break;
            
        default:
            break;
    }
    
    SlideAnimation *walkAnimation = new SlideAnimation(Constants::TickPerFrame_MoveAnimation, true, true);
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId - 1));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId + 1));
    walkAnimation->appendFrame(filenameForBattleFieldAnimation(creatureAniId, centerImageId));
    std::string key = StringUtils::format("Walk-%02d-%03d", direction, creatureAniId);
    _slideAnimationDictionary->insert(key, walkAnimation);
    walkAnimation->release();
}

void AnimationLibrary::loadScopeIndicatorAnimation()
{
    std::string key = "ScopeIndicator";
    
    SlideAnimation *animation = new SlideAnimation(Constants::TickPerFrame_IdleAnimation, true, true);
    
    animation->appendFrame(TransparencyFrame::create(40));
    animation->appendFrame(TransparencyFrame::create(60));
    animation->appendFrame(TransparencyFrame::create(80));
    animation->appendFrame(TransparencyFrame::create(100));
    animation->appendFrame(TransparencyFrame::create(120));
    animation->appendFrame(TransparencyFrame::create(100));
    animation->appendFrame(TransparencyFrame::create(80));
    animation->appendFrame(TransparencyFrame::create(60));
    
    _slideAnimationDictionary->insert(key, animation);
    animation->release();
}

void AnimationLibrary::loadMenuAnimation(int menuItemId)
{
    std::string key = StringUtils::format("Menu-%d", menuItemId);
    SlideAnimation *animation = new SlideAnimation(Constants::TickPerFrame_IdleAnimation, true, true);
    
    animation->appendFrame(StringUtils::format("Menu/Menu-%03d-1.png", menuItemId));
    animation->appendFrame(StringUtils::format("Menu/Menu-%03d-2.png", menuItemId));
    
    _slideAnimationDictionary->insert(key, animation);
    animation->release();
}

SlideAnimation * AnimationLibrary::getIdleAnimation(int creatureAniId, bool greyout)
{
    std::string key = StringUtils::format("Idle-%03d-%d", creatureAniId, greyout);
    
    if (_slideAnimationDictionary->at(key) == nullptr)
    {
        this->loadIdleAnimation(creatureAniId, greyout);
    }
    
    return _slideAnimationDictionary->at(key);
}

SlideAnimation * AnimationLibrary::getWalkAnimation(int creatureAniId, Direction direction)
{
    std::string key = StringUtils::format("Walk-%02d-%03d", direction, creatureAniId);
    
    if (_slideAnimationDictionary->at(key) == nullptr)
    {
        this->loadWalkAnimation(creatureAniId, direction);
    }

    return _slideAnimationDictionary->at(key);
}

SlideAnimation * AnimationLibrary::getDeadAnimation(int creatureAniId)
{
    std::string key = StringUtils::format("Dead-%03d", creatureAniId);
    
    if (_slideAnimationDictionary->at(key) == nullptr)
    {
        this->loadDeadAnimation(creatureAniId);
    }
    
    return _slideAnimationDictionary->at(key);
}

SlideAnimation * AnimationLibrary::getScopeIndicatorAnimation()
{
    std::string key = "ScopeIndicator";
    if (_slideAnimationDictionary->at(key) == nullptr)
    {
        this->loadScopeIndicatorAnimation();
    }
    
    return _slideAnimationDictionary->at(key);
}

SlideAnimation * AnimationLibrary::getMenuAnimation(int menuItemId)
{
    std::string key = StringUtils::format("Menu-%d", menuItemId);
    if (_slideAnimationDictionary->at(key) == nullptr)
    {
        this->loadMenuAnimation(menuItemId);
    }
    
    return _slideAnimationDictionary->at(key);
}

std::string AnimationLibrary::filenameForBattleFieldAnimation(int creatureAniId, int index)
{
    return StringUtils::format("Icons/%03d/Icon-%03d-%02d.png", creatureAniId, creatureAniId, index);
}
