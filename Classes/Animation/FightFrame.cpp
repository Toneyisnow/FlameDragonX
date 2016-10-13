//
//  FightFrame.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/12/16.
//
//

#include "FightFrame.hpp"


FightFrame::FightFrame(std::string filename, FightFrameDefinition * def)
: FDFrame(filename)
{
    _definition = def;
}

FightFrameDefinition * FightFrame::getDefinition()
{
    return _definition;
}
