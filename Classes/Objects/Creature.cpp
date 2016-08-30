//
//  Creature.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "Creature.hpp"
#include "SlideAnimation.hpp"
#include "CreatureDefinition.hpp"
#include "AnimationLibrary.hpp"

Creature::Creature(CreatureType type)
{
    this->_creatureType = type;
    
    this->_gestureStatus = GestureStatus_Idle;
    // this->initialize();
    
}

Creature::~Creature()
{
    
}

void Creature::initWithDefinition(int identity, int creatureId)
{
    
    // CreatureDefinition * definition = new CreatureDefinition(creatureId);
    
    SlideAnimation * animation = AnimationLibrary::getInstance()->getIdleAnimation(1);
    _animator->setAnimation(animation);
}


CreatureType Creature::getType()
{
    return _creatureType;
}

void Creature::setGesture(GestureStatus gesture)
{
    if (this->_gestureStatus == gesture)
    {
        return;
    }
    
    this->_gestureStatus = gesture;
    SlideAnimation * animation;
    int animationId = 1;
    
    switch (gesture) {
        case GestureStatus_Idle:
            animation = AnimationLibrary::getInstance()->getIdleAnimation(animationId);
            _animator->setAnimation(animation);
            break;
        case GestureStatus_WalkingUp:
            animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, DirectionUp);
            _animator->setAnimation(animation);
            break;
        case GestureStatus_WalkingDown:
            animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, DirectionDown);
            _animator->setAnimation(animation);
            break;
        case GestureStatus_WalkingLeft:
            animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, DirectionLeft);
            _animator->setAnimation(animation);
            break;
        case GestureStatus_WalkingRight:
            animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, DirectionRight);
            _animator->setAnimation(animation);
            break;
            
        default:
            break;
    }
}
