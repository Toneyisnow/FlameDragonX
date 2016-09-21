//
//  BattleObject.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "BattleObject.hpp"
#include "FDActivity.hpp"

BattleObject::BattleObject(BattleObjectType type)
{
    _objectType = type;

}

BattleObject::~BattleObject()
{
    _animator->release();
}

BattleObjectType BattleObject::getObjectType()
{
    return _objectType;
}

void BattleObject::initialize(std::string filename)
{
    _baseSprite = Sprite::create(filename);
    _animator = new FDAnimate(_baseSprite);
}


void BattleObject::takeTick(int synchronizedTick)
{
    _animator->takeTick(synchronizedTick);
}

Sprite* BattleObject::getSprite()
{
    return _baseSprite;
}

void BattleObject::setDirection(Direction direction)
{
    _direction = direction;
}

void BattleObject::setAnimation(SlideAnimation * animation)
{
    _animator->setAnimation(animation);
}

bool BattleObject::animationStopped()
{
    return _animator->hasFinished();
}

FDActivity * BattleObject::onRemovalActivity()
{
    return nullptr;
}

void BattleObject::setZOrder(int zOrder)
{
    _baseSprite->setLocalZOrder(zOrder);
}