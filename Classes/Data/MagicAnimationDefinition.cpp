//
//  MagicAnimationDefinition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/20/16.
//
//

#include "MagicAnimationDefinition.hpp"

MagicAnimationDefinition::MagicAnimationDefinition(int magicId, MagicAnimationType type)
{
    _magicId = magicId;
    _type = type;
}

void MagicAnimationDefinition::readFromFile(TextFileReader * reader)
{
    int frameCount = reader->readInt();
    
    for (int i = 1; i <= frameCount; i++) {
        std::string filename = StringUtils::format("Magic-%03d-%02d.png", magicAnimationId(), i);
        
        int hittingRateInt = reader->readInt();
        
        int interval = 100; // ??
        int soundId = 0;
        bool isRemote = false;
        float hittingRate = hittingRateInt / 100.0f;
        FightFrameDefinition * frame = new FightFrameDefinition(interval, soundId, isRemote, hittingRate);
        _frameList.pushBack(frame);
        frame->release();
    }
}

int MagicAnimationDefinition::magicAnimationId()
{
    return _magicId * 10 + _type;
}

Vector<FightFrameDefinition *> MagicAnimationDefinition::frameList()
{
    return _frameList;
}
