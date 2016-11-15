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
    MessageBoxOperatingType_Equip,
    MessageBoxOperatingType_Use
    
} MessageBoxOperatingType;

#include "cocos2d.h"
#include "Creature.hpp"
#include "ScaledSprite.hpp"
#include "CallbackMethod.hpp"

USING_NS_CC;

class SelectableBox : public cocos2d::Ref
{
protected:
    
    Creature * _creature;
    
    MessageBoxOperatingType _operatingType;
    
    ScaledSprite * _baseSprite;
    
    Ref * _caller;
    SEL_CALLBACK1 _callerMethod;
    
    float _initialX;
    float _initialY;
    float _spacingX;
    float _spacingY;
    
    int _objectCount;
    
public:
    
    SelectableBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method);
    
    ScaledSprite * getSprite();
    
    // virtual void drawObjects();
    int handleClick(Vec2 location);
    
};

#endif /* SelectableBox_hpp */
