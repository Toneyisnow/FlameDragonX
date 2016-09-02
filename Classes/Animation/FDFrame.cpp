//
//  SpriteFrame.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "FDFrame.hpp"


FDFrame::FDFrame(std::string filename)
: FDFrame(filename, Vec2(0, 0), 0)
{

}

FDFrame::FDFrame(std::string filename, int tickCount)
: FDFrame(filename, Vec2(0, 0), tickCount)
{
    
}
FDFrame::FDFrame(std::string filename, Vec2 offset, int tickCount)
{
    
    this->_texture = Director::getInstance()->getTextureCache()->addImage(filename);
    this->_offset = offset;
    this->_opacity = -1;
    this->_tickCount = tickCount;
}

FDFrame::FDFrame(std::string filename, float opacity)
{
    
    this->_texture = Director::getInstance()->getTextureCache()->addImage(filename);
    this->_offset = Vec2(0, 0);
    this->_opacity = _opacity;
    this->_tickCount = 0;
}

FDFrame::~FDFrame()
{
    
}

void FDFrame::setTickCount(int count)
{
    this->_tickCount = count;
}

Texture2D * FDFrame::getTexture()
{
    return this->_texture;
}

Vec2 FDFrame::getOffset()
{
    return this->_offset;
}

int FDFrame::getTickCount()
{
    return this->_tickCount;
}


void FDFrame::renderFrame(Sprite * sprite)
{
    sprite->setTexture(_texture);
    
    if (_opacity >= 0) {
        sprite->setOpacity(_opacity);
    }
}
