//
//  SpeakMessage.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef SpeakMessage_hpp
#define SpeakMessage_hpp

#include "cocos2d.h"
#include "ConversationMessage.hpp"
#include "Creature.hpp"

class SpeakMessage : public ConversationMessage
{
private:
    
    
public:
    
    SpeakMessage(std::string content);
    SpeakMessage(Creature * creature, std::string content);
    

};

#endif /* SpeakMessage_hpp */
