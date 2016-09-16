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
#include "Message.hpp"
#include "Creature.hpp"

class SpeakMessage : public Message
{
private:
    
    Sprite * _messageBox;
    
    Creature * _creature;
    std::string _content;
    
public:
    
    SpeakMessage(std::string content);
    SpeakMessage(Creature * creature, std::string content);
    
    
    void initDialog() override;
    void removeDialog() override;
    FDActivity * onEnterActivity() override;
    FDActivity * onExitActivity() override;
    
    void handleClick(Vec2 location) override;
    
};

#endif /* SpeakMessage_hpp */
