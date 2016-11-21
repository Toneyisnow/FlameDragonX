//
//  FightAnimation.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#include "FightAnimation.hpp"
#include "cocos2d.h"
#include "FightFrame.hpp"

FightAnimation::FightAnimation(FightAnimationDefinition * def)
: SlideAnimation(Constants::TickPerFrame_FightAnimation, false, false)
{
    //// _definition = def;
    _frameDefinitionList = def->frameList();
    
    for(int frameIndex = 0; frameIndex < _frameDefinitionList.size(); frameIndex ++)
    {
        std::string filename = StringUtils::format("Fights/%03d/Fight-%03d-%d-%02d.png", def->animationId(), def->animationId(), def->type(), frameIndex + 1);
        
        FightFrame * frame = new FightFrame(filename, _frameDefinitionList.at(frameIndex));
        appendFrame(frame);
        frame->release();
    }
}

FightAnimation::FightAnimation(MagicAnimationDefinition * def)
: SlideAnimation(Constants::TickPerFrame_FightAnimation, false, false)
{
    //// _definition = def;
    _frameDefinitionList = def->frameList();
    
    for(int frameIndex = 0; frameIndex < _frameDefinitionList.size(); frameIndex ++)
    {
        std::string filename = StringUtils::format("Magic/%03d/Magic-%03d-%02d.png", def->magicAnimationId(), def->magicAnimationId(), frameIndex + 1);
        
        FightFrame * frame = new FightFrame(filename, _frameDefinitionList.at(frameIndex));
        appendFrame(frame);
        frame->release();
    }
}

bool FightAnimation::isRemoteAttack()
{
    for (FightFrameDefinition * frameDef : _frameDefinitionList) {
        if (frameDef->isRemote()) {
            return true;
        }
    }
    
    return false;
}

