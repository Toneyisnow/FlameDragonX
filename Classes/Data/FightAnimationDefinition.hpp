//
//  FightAnimationDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#ifndef FightAnimationDefinition_hpp
#define FightAnimationDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FightFrameDefinition.hpp"

typedef enum FightAnimationType
{
    FightAnimationType_Idle = 1,
    FightAnimationType_Attack = 2,
    FightAnimationType_Skill = 3
    
} FightAnimationType;

class FightAnimationDefinition : public cocos2d::Ref
{
private:
    
    int _animationId;
    FightAnimationType _type;
    Vector<FightFrameDefinition *> _frameList;
    
public:
    
    FightAnimationDefinition(int animationId, FightAnimationType type);
    
    void readFromFile(TextFileReader * reader);
    
    int animationId();
    FightAnimationType type();
    
    Vector<FightFrameDefinition *> frameList();
    
    
};

#endif /* FightAnimationDefinition_hpp */
