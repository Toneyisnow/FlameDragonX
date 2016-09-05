//
//  BattleObject.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "BattleObject.hpp"

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
