//
//  FightAnimationDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#include "FightAnimationDefinition.hpp"

FightAnimationDefinition::FightAnimationDefinition(int animationId, FightAnimationType type)
{
    _animationId = animationId;
    _type = type;
    
}

void FightAnimationDefinition::readFromFile(TextFileReader * reader)
{
    int frameCount = reader->readInt();
    int hitArray[frameCount];
    int remoteFrameIndex = 0;
    
    if (_type == FightAnimationType_Attack)
    {
        int next = reader->readInt();
        int index = 1;
        while (next != -1) {
            hitArray[index -1] = next;
            index ++;
            next = reader->readInt();
        }
        
        remoteFrameIndex = reader->readInt();
    }
    
    for (int i = 1; i <= frameCount; i++) {
        std::string filename = StringUtils::format("Fight-%03d-%d-%02d.png", _animationId, _type, i);
        
        int interval = 100; // ??
        int soundId = 0;
        bool isRemote = (i <= remoteFrameIndex);
        float hittingRate = (_type == FightAnimationType_Attack) ? hitArray[i - 1] / 100.0f : 0;
        FightFrameDefinition * frame = new FightFrameDefinition(interval, soundId, isRemote, hittingRate);
        _frameList.pushBack(frame);
        frame->release();
    }
}

int FightAnimationDefinition::animationId()
{
    return _animationId;
}

FightAnimationType FightAnimationDefinition::type()
{
    return _type;
}

Vector<FightFrameDefinition *> FightAnimationDefinition::frameList()
{
    return _frameList;
}
