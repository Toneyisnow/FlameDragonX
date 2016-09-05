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
: BattleObject(BattleObject_Creature)
{
    this->_creatureType = type;
    
    this->_gestureStatus = GestureStatus_Idle;
    // this->initialize();
    
    initialize("Others/WhiteBlock.png");
}

Creature::~Creature()
{
    _data->release();
}



int Creature::getId()
{
    return _identifier;
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
    
    
    SlideAnimation * animation = AnimationLibrary::getInstance()->getIdleAnimation(_definition->animationId);
    _animator->setAnimation(animation);
}


CreatureType Creature::getType()
{
    return _creatureType;
}

void Creature::setDirection(Direction direction)
{
    if (_direction == direction)
    {
        return;
    }
    
    BattleObject::setDirection(direction);
    SlideAnimation * animation;
    int animationId = _definition->animationId;
    
    if (direction == DirectionNone)
    {
        animation = AnimationLibrary::getInstance()->getIdleAnimation(animationId);
        _animator->setAnimation(animation);
    }
    else
    {
        animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, direction);
        _animator->setAnimation(animation);
    }
}


// Deprecated
void Creature::setGesture(GestureStatus gesture)
{
    if (this->_gestureStatus == gesture)
    {
        return;
    }
    
    this->_gestureStatus = gesture;
    SlideAnimation * animation;
    int animationId = _definition->animationId;
    
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

bool Creature::isVisible()
{
    return true;
}

bool Creature::isDead()
{
    return (_data->hpCurrent <= 0);
}