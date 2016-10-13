//
//  FightFrame.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/12/16.
//
//

#ifndef FightFrame_hpp
#define FightFrame_hpp

#include "cocos2d.h"
#include "FDFrame.hpp"
#include "FightFrameDefinition.hpp"

class FightFrame : public FDFrame
{
private:
    
    FightFrameDefinition * _definition;
    
public:
    
    FightFrame(std::string filename, FightFrameDefinition * def);
    
    FightFrameDefinition * getDefinition();
    
};

#endif /* FightFrame_hpp */
