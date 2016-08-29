//
//  BattleObject.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "BattleObject.hpp"

BattleObject::BattleObject()
{
    _baseSprite = Sprite::create("Icons/001/Icon-001-02.png");
    _animator = new FDAnimate(_baseSprite);

}

BattleObject::~BattleObject()
{
    _animator->release();
}


void BattleObject::initialize()
{
}


void BattleObject::takeTick(int synchronizedTick)
{
    _animator->takeTick(synchronizedTick);
}

Sprite* BattleObject::getSprite()
{
    return _baseSprite;
}