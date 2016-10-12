//
//  FightAnimation.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#include "FightAnimation.hpp"
#include "cocos2d.h"

FightAnimation::FightAnimation(FightAnimationDefinition * def)
: SlideAnimation(Constants::TickPerFrame_FightAnimation, false, false)
{
    _definition = def;
    
    for(int frameIndex = 0; frameIndex < _definition->frameList().size(); frameIndex ++)
    {
        std::string filename = StringUtils::format("Fights/%03d/Fight-%03d-%d-%02d.png", def->animationId(), def->animationId(), def->type(), frameIndex + 1);
        appendFrame(filename);
    }
}

bool FightAnimation::isRemoteAttack()
{
    for (FightFrameDefinition * frameDef : _definition->frameList()) {
        if (frameDef->isRemote()) {
            return true;
        }
    }
    
    return false;
}


void FightAnimation::setTagIndex(int tag)
{
    _tagIndex = tag;
}

void FightAnimation::setCounterScene(CounterScene * scene)
{
    _scene = scene;
}
