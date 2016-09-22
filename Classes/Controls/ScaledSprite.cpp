//
//  ScaledSprite.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#include "ScaledSprite.hpp"

ScaledSprite* ScaledSprite::create(const std::string& filename)
{
    ScaledSprite *sprite = new (std::nothrow) ScaledSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void ScaledSprite::setScaledPosition(Vec2 position)
{
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    
    setPosition(Vec2(position.x / scaleFactor, position.y / scaleFactor));
}

void ScaledSprite::setScale(float scale)
{
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    
    Sprite::setScale(scale * scaleFactor);
}

void ScaledSprite::addChild(Node * child, Vec2 position)
{
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    child->setPosition(Vec2(position.x / scaleFactor, position.y / scaleFactor));
    
    cocos2d::Node::addChild(child);
    
}

void ScaledSprite::addLabel(Label * label, Vec2 position)
{
    float scaleFactor = Director::getInstance()->getContentScaleFactor();
    label->setScale(1 / scaleFactor);
    addChild(label, position);
}

