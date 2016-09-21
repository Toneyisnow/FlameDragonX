//
//  ConversationMessage.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef ConversationMessage_hpp
#define ConversationMessage_hpp

#include "Message.hpp"
#include "Creature.hpp"

class ConversationMessage : public Message
{
protected:
    
    Sprite * _messageBox;
    
    Creature * _creature;
    std::string _content;
    
    Vec2 _upScreen;
    Vec2 _downScreen;
    
    
public:
    
    ConversationMessage(std::string content);
    ConversationMessage(Creature * creature, std::string content);
    
    
    void initDialog() override;
    void removeDialog() override;
    void buildBaseDialog(Vec2 screenPosition);

    FDActivity * onEnterActivity() override;
    FDActivity * onExitActivity() override;
    
    void handleClick(Vec2 location) override;
    
};

#endif /* ConversationMessage_hpp */
