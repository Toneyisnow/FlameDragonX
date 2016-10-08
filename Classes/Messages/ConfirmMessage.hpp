//
//  ConfirmMessage.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef ConfirmMessage_hpp
#define ConfirmMessage_hpp

#include "cocos2d.h"
#include "ConversationMessage.hpp"

class ConfirmMessage : public ConversationMessage
{
private:
    
public:
    
    ConfirmMessage(std::string content);
    ConfirmMessage(Creature * creature, std::string content);

    void handleClick(Vec2 location) override;

};

#endif /* ConfirmMessage_hpp */
