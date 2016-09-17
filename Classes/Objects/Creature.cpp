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
    
    initialize("Others/Empty.png");
}

Creature::~Creature()
{
    _data->release();
}

CreatureData * Creature::creatureData()
{
    return _data;
}

CreatureDefinition * Creature::getDefinition()
{
    return _definition;
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
        FDNumber * itemId = _definition->initialItemList->at(m);
        _data->itemList->pushBack(itemId);
        ItemDefinition * definition = DataStore::getInstance()->getItemDefinition(itemId->getValue());
        if (definition->isAttackItem())
        {
            _data->attackItemIndex = m;
        }
        else if (definition->isDefendItem())
        {
            _data->defendItemIndex = m;
        }
    }
    for (int m = 0; m < _definition->initialMagicList->size(); m++) {
        _data->magicList->pushBack(_definition->initialMagicList->at(m));
    }
    
    startTurn();
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
        animation = AnimationLibrary::getInstance()->getIdleAnimation(animationId, false);
        _animator->setAnimation(animation);
    }
    else
    {
        animation = AnimationLibrary::getInstance()->getWalkAnimation(animationId, direction);
        _animator->setAnimation(animation);
    }
}

/*
void Creature::setFocus(bool isFocus)
{
    if (isFocus)
    {
        _baseSprite->setLocalZOrder(BattleObjectOrder_FocusCreature);
    }
    else
    {
        _baseSprite->setLocalZOrder(BattleObjectOrder_Creature);
    }
}
*/

void Creature::endTurn()
{
    _hasActioned = true;
    
    SlideAnimation *animation = AnimationLibrary::getInstance()->getIdleAnimation(_definition->animationId, true);
    _animator->setAnimation(animation);
}

void Creature::startTurn()
{
    _hasActioned = false;
    _hasMoved = false;
    
    SlideAnimation *animation = AnimationLibrary::getInstance()->getIdleAnimation(_definition->animationId, false);
    _animator->setAnimation(animation);
}

bool Creature::isVisible()
{
    return true;
}

bool Creature::canFly()
{
    return _definition->canFly();
}

bool Creature::isDead()
{
    return (_data->hpCurrent <= 0);
}

bool Creature::isFrozen()
{
    return false;
}

bool Creature::hasTakenAction()
{
    return _hasActioned;
}

FDRange * Creature::getAttackRange()
{
    AttackItemDefinition * attackItem = _data->getAttackItem();
    if (attackItem == nullptr)
    {
        return nullptr;
    }
    
    return attackItem->attackRange();
}
