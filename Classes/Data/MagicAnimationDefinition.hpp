//
//  MagicAnimationDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/20/16.
//
//

#ifndef MagicAnimationDefinition_hpp
#define MagicAnimationDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FightFrameDefinition.hpp"

typedef enum MagicAnimationType
{
    MagicAnimationType_Good = 1,
    MagicAnimationType_Bad = 2
    
} MagicAnimationType;

class MagicAnimationDefinition : public cocos2d::Ref
{
private:
    
    int _magicId;
    MagicAnimationType _type;
    Vector<FightFrameDefinition *> _frameList;
    
public:
    
    MagicAnimationDefinition(int magicId, MagicAnimationType type);
    
    void readFromFile(TextFileReader * reader);
    
    int magicAnimationId();
    
    Vector<FightFrameDefinition *> frameList();
    
};

#endif /* MagicAnimationDefinition_hpp */
