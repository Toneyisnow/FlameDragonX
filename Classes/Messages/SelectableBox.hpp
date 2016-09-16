//
//  SelectableBox.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#ifndef SelectableBox_hpp
#define SelectableBox_hpp

typedef enum MessageBoxOperatingType
{
    MessageBoxOperatingType_Select,
    MessageBoxOperatingType_ShowOnly,
    MessageBoxOperatingType_Equip
} MessageBoxOperatingType;

#include "cocos2d.h"
#include "Creature.hpp"

USING_NS_CC;

class SelectableBox : public cocos2d::Ref
{
protected:
    
    Creature * _creature;
    
    MessageBoxOperatingType _operatingType;
    
    Sprite * _baseSprite;
    
public:
    
    SelectableBox();
    
    Sprite * getSprite();
};

#endif /* SelectableBox_hpp */
