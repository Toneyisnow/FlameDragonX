//
//  SlideAnimation.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#include "SlideAnimation.hpp"

SlideAnimation::SlideAnimation(int defaultFrameTickCount, bool isRepeatable,  bool isSynchronized)
{
    this->_defaultFrameTickCount = defaultFrameTickCount;
    this->_isRepeatable = isRepeatable;
    this->_isSynchronized = isSynchronized;
    this->_totalTick = 0;
    
    _frameList.clear();
}

SlideAnimation::~SlideAnimation()
{
    _frameList.clear();
}

void SlideAnimation::appendFrame(FDFrame * frame)
{
    _frameList.pushBack(frame);
    
    if (frame->getTickCount() == 0)
    {
        frame->setTickCount(_defaultFrameTickCount);
    }
    
    _totalTick += frame->getTickCount();
}

void SlideAnimation::appendFrame(std::string filename)
{
    FDFrame * frame = new FDFrame(filename);
    this->appendFrame(frame);
    frame->release();
}

void SlideAnimation::appendFrame(Texture2D * texture)
{
    FDFrame * frame = new FDFrame(texture);
    this->appendFrame(frame);
    frame->release();
}

int SlideAnimation::getFrameCount()
{
    return _frameList.size();
}

FDFrame * SlideAnimation::frameAt(int index)
{
    if (index < 0 || index >= _frameList.size())
    {
        log("Error getting SlideAnimation: out of index");
        return nullptr;
    }
    
    return _frameList.at(index);
}

FDFrame * SlideAnimation::frameAtTick(int tick)
{
    if (tick < 0 || tick >= _totalTick)
    {
        return nullptr;
    }
    
    for (int i = 0 ; i < _frameList.size(); i++)
    {
        FDFrame * frame = _frameList.at(i);
        if (tick < frame->getTickCount())
        {
            return frame;
        }
        
        tick -= frame->getTickCount();
    }
    
    return nullptr;
}


bool SlideAnimation::isRepeatable()
{
    return _isRepeatable;
}

bool SlideAnimation::isSynchronized()
{
    return _isSynchronized;
}

int SlideAnimation::getTotalTick()
{
    return _totalTick;
}
