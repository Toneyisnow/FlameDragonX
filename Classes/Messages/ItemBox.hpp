//
//  ItemBox.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef ItemBox_hpp
#define ItemBox_hpp

#include "cocos2d.h"
#include "SelectableBox.hpp"
#include "ItemDefinition.hpp"

class ItemBox : public SelectableBox
{
private:
    
    bool isSelectable(ItemDefinition * item);
    
public:
    
    ItemBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method);
    
};

#endif /* ItemBox_hpp */
