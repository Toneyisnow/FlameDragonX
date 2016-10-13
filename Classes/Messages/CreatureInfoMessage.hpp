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
    
    const float MESSAGEBOX_SCALE = 1.1f;
    
    const Vec2 _leftPosition = Vec2(120, Constants::getScreenSize().height - 50);
    const Vec2 _rightPosition = Vec2(360, Constants::getScreenSize().height - 50);
    
    ScaledSprite * _baseSprite;
    
    Creature * _creature;
    
    Vec2 _position;
    
    Sprite * _hpBar;
    Sprite * _mpBar;
    Label * _hpLabel;
    Label * _mpLabel;
    
public:
    
    CreatureInfoMessage(Creature * creature);
    CreatureInfoMessage(Creature * creature, Vec2 clickedAtLocation);
    
    void initDialog() override;
    void removeDialog() override;
    
    void setPosition(Vec2 position);
    
    void setHp(int hpValue);
    void setMp(int mpValue);
    
    void appear();
    void hide();
    
    void setZOrder(int order);
    
};

#endif /* CreatureInfoMessage_hpp */
