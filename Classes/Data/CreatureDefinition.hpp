//
//  CreatureDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef CreatureDefinition_hpp
#define CreatureDefinition_hpp

#include "cocos2d.h"

USING_NS_CC;

class CreatureDefinition : public Ref
{
private:
    
    int _definitionId;
    int _animationId;
    
public:
    
    CreatureDefinition(int defId);
    
    int getDefinitionId();
    int getAnimationId();
    
    
    
};
#endif /* CreatureDefinition_hpp */
