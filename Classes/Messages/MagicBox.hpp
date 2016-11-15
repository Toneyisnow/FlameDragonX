//
//  MagicBox.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef MagicBox_hpp
#define MagicBox_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "SelectableBox.hpp"

class MagicBox : public SelectableBox
{
private:
    
    
public:
    
    MagicBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method);
    
    
};

#endif /* MagicBox_hpp */
