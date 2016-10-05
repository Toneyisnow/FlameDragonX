//
//  MessageBox.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef MessageBox_hpp
#define MessageBox_hpp

#include "cocos2d.h"
#include "Message.hpp"
#include "DatoBar.hpp"
#include "DetailBar.hpp"
#include "SelectableBox.hpp"
#include "ScaledSprite.hpp"

typedef enum MessageBoxType
{
    MessageBoxType_Item,
    MessageBoxType_Magic
} MessageBoxType;

class CompositeBox : public Message
{
private:
    
    MessageBoxType _type;
    MessageBoxOperatingType _operatingType;
    
    Creature * _creature;
    
    DatoBar * _datoBar;
    DetailBar * _detailBar;
    SelectableBox * _mainBox;
    
    Vec2 _datoPosition0;
    Vec2 _datoPosition1;
    Vec2 _detailPosition0;
    Vec2 _detailPosition1;
    Vec2 _mainPosition0;
    Vec2 _mainPosition1;
    
    float _flyInflyOutDuration;
    
public:
    
    CompositeBox(Creature * creature, MessageBoxType type, MessageBoxOperatingType oType);
    ~CompositeBox();
    
    void addComponent(ScaledSprite * component, Vec2 anchorPoint, Vec2 position);
    
    void initDialog() override;
    void removeDialog() override;
    FDActivity * onEnterActivity() override;
    FDActivity * onExitActivity() override;
    
    void handleClick(Vec2 location) override;
};

#endif /* MessageBox_hpp */
