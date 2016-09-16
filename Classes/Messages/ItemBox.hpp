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

class ItemBox : public SelectableBox
{
private:
    
public:
    
    ItemBox(Creature * creature, MessageBoxOperatingType type);
    
};

#endif /* ItemBox_hpp */
