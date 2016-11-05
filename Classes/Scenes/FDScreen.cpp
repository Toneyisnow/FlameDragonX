//
//  FDScreen.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#include "FDScreen.hpp"
#include "Constants.hpp"

FDScreen::FDScreen(Layer* layer)
{
    _layer = layer;
    _screenSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    _scaleFactor = Director::getInstance()->getContentScaleFactor();
    
}

FDScreen::FDScreen(Layer* layer, int width, int height, bool keepSameScale)
{
    auto size = Director::getInstance()->getWinSize();
    auto sizein = Director::getInstance()->getWinSizeInPixels();
    
    _dpi = sizein.width / size.width;
    
    if (width <=0 || height <= 0)
    {
        throw new std::exception();
    }
    
    this->_layer = layer;
    this->_width = width;
    this->_height = height;
    this->_keepSameScale = keepSameScale;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    _scaleX = visibleSize.width / width;
    _scaleY = visibleSize.height / height;
    _offsetX = 0;
    _offsetY = 0;
    
    if (keepSameScale)
    {
        _scaleX = (_scaleX < _scaleY) ? _scaleX : _scaleY;
        _scaleY = _scaleX;
        _offsetX = (visibleSize.width - width * _scaleX) / 2;
        _offsetY = (visibleSize.height - height * _scaleY) / 2;
    }
}

void FDScreen::addToWindow(Node * node, Vec2 position, float scale, int zOrder)
{
    node->setPosition(position);
    node->setScale(_scaleFactor * scale);
    // node->setScale(Constants::DEFAULT_SPRITE_SCALE * _scaleFactor * scale);
    
    _layer->addChild(node, zOrder);
}

void FDScreen::addToWindow(Node * node, Vec2 position, int zOrder)
{
    node->setPosition(position);
    // node->setScale(Constants::DEFAULT_SPRITE_SCALE * _scaleFactor);
    
    _layer->addChild(node, zOrder);
}

void FDScreen::addToWindow(Node * node, Vec2 position, Size shownSize, int zOrder)
{
    this->addToWindow(node, position, zOrder);
    
    Size nodeSize = node->getContentSize();
    float scaleX = shownSize.width / nodeSize.width;
    float scaleY = shownSize.height / nodeSize.height;
    node->setScale(scaleX, scaleY);
}

void FDScreen::addToVisible(Node * node, Vec2 position, int zOrder)
{
    addToVisible(node, position, 1, zOrder);
}

void FDScreen::addToVisible(Node * node, Vec2 position, float scale, int zOrder)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 visiblePosition = Vec2(origin.x + position.x, origin.y + position.y);
    
    addToWindow(node, visiblePosition, scale, zOrder);
}


void FDScreen::addChild(Node * node, int x, int y, int zOrder)
{
    Size nodeSize = node->getContentSize();
    addChild(node, x, y, nodeSize.width, nodeSize.height, zOrder);
}

void FDScreen::addChild(Node * node, int x, int y, int displayWidth, int displayHeight, int zOrder)
{
    if (node == nullptr)
        return;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float posX = x * _scaleX;
    float posY = y * _scaleY;
    
    Size nodeSize = node->getContentSize();
    
    float nodeScaleX = visibleSize.width  / _width * displayWidth / nodeSize.width * _dpi;
    float nodeScaleY = visibleSize.height  / _height * displayHeight / nodeSize.height * _dpi;
    
    if (_keepSameScale)
    {
        nodeScaleX = (nodeScaleX < nodeScaleY) ? nodeScaleX : nodeScaleY;
        nodeScaleY = nodeScaleX;
    }
    
    node->setPosition(origin.x + posX + _offsetX, origin.y + posY + _offsetY);
    node->setScale(nodeScaleX, nodeScaleY);
    
    this->_layer ->addChild(node, zOrder);
    
    
}
