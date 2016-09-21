//
//  SpeakMessage.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "SpeakMessage.hpp"
#include "MessageLayer.hpp"

SpeakMessage::SpeakMessage(std::string content)
: ConversationMessage(content)
{

}

SpeakMessage::SpeakMessage(Creature * creature, std::string content)
: ConversationMessage(creature, content)
{

}
