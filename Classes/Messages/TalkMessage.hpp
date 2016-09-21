//
//  TalkMessage.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef TalkMessage_hpp
#define TalkMessage_hpp

#include "cocos2d.h"
#include "ConversationMessage.hpp"

class TalkMessage : public ConversationMessage
{
private:
    
public:
    
    TalkMessage(Creature * creature, std::string content);

    
};

#endif /* TalkMessage_hpp */
