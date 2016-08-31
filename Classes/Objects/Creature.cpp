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
#include "DataStore.hpp"

Creature::Creature(CreatureType type)
{
    this->_creatureType = type;
    
    this->_gestureStatus = GestureStatus_Idle;
    // this->initialize();
    
    
}

Creature::~Creature()
{
    _data->release();
}

void Creature::initWithDefinition(int identity, int creatureId)
{
    this->_identifier = identity;
    _definition = DataStore::getInstance()->getCreatureDefinition(creatureId);
    
    _data = new CreatureData();
    _data->level = _definition->initialLevel;
    _data->ap = _definition->initialAP;
    _data->dp = _definition->initialDP;
    _data->dx = _definition->initialDX;
    _data->mv = _definition->initialMV;
    _data->ex = _definition->initialEX;
    
    _data->hpCurrent = _data->hpMax = _definition->initialHP;
    _data->mpCurrent = _data->mpMax = _definition->initialMP;
    
    for (int m = 0; m < _definition->initialItemList->size(); m++) {
        _data->itemList->pushBack(_definition->initialItemList->at(m));
    }
    for (int m = 0; m < _definition->initialMagicList->size(); m++) {
        _data->magicList->pushBack(_definition->initialMagicList->at(m));
    }
    
    
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
