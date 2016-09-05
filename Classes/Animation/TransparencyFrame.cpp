//
//  TransparencyFrame.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#include "TransparencyFrame.hpp"

TransparencyFrame * TransparencyFrame::create(float opacity)
{
    TransparencyFrame * frame = new TransparencyFrame(opacity);
    frame->autorelease();
    
    return frame;
}

TransparencyFrame::TransparencyFrame(float opacity)
: FDFrame ()
{
    this->_opacity = opacity;
}

TransparencyFrame::~TransparencyFrame()
{
    
}

void TransparencyFrame::renderFrame(Sprite * sprite)
{
    sprite->setOpacity(_opacity);
}