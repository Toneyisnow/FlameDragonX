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

typedef enum MessageBoxType
{
    MessageBoxType_Item,
    MessageBoxType_Magic
} MessageBoxType;


class MessageBox : public Message
{
private:
    
    MessageBoxType _type;
    
    
public:
    
    
};

#endif /* MessageBox_hpp */
