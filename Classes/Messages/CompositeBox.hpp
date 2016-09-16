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
    
public:
    
    CompositeBox(Creature * creature, MessageBoxType type, MessageBoxOperatingType oType);
    ~CompositeBox();
    
    void initDialog() override;
    void removeDialog() override;
    FDActivity * onEnterActivity() override;
    FDActivity * onExitActivity() override;
    
    void handleClick(Vec2 location) override;
};

#endif /* MessageBox_hpp */
