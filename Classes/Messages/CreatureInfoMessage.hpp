//
//  CreatureInfoMessage.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/21/16.
//
//

#ifndef CreatureInfoMessage_hpp
#define CreatureInfoMessage_hpp

#include "cocos2d.h"
#include "Message.hpp"
#include "Creature.hpp"
#include "ScaledSprite.hpp"

class CreatureInfoMessage : public Message
{
private:
    
    const Vec2 _leftPosition = Vec2(120, Constants::getScreenSize().height - 50);
    const Vec2 _rightPosition = Vec2(360, Constants::getScreenSize().height - 50);
    
    ScaledSprite * _baseSprite;
    
    Creature * _creature;
    
    Vec2 _position;
    
public:
    
    CreatureInfoMessage(Creature * creature, Vec2 clickedAtLocation);
    
    void initDialog() override;
    void removeDialog() override;
    
};

#endif /* CreatureInfoMessage_hpp */