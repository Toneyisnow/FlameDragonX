//
//  SpriteFrame.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "FDFrame.hpp"

FDFrame::FDFrame()
{
    this->_tickCount = 0;
}

FDFrame::FDFrame(std::string filename)
: FDFrame(filename, 0)
{

}

FDFrame::FDFrame(std::string filename, int tickCount)
{
    // Director::getInstance()->getTextureCache()->image
    this->_texture = Director::getInstance()->getTextureCache()->addImage(filename);
    this->_texture->retain();
    this->_tickCount = tickCount;
}

FDFrame::~FDFrame()
{
    this->_texture->release();
}

void FDFrame::setTickCount(int count)
{
    this->_tickCount = count;
}

Texture2D * FDFrame::getTexture()
{
    return this->_texture;
}


int FDFrame::getTickCount()
{
    return this->_tickCount;
}


void FDFrame::renderFrame(Sprite * sprite)
{
    sprite->setTexture(_texture);
}
