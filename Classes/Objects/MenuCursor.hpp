//
//  MenuCursor.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/6/16.
//
//

#ifndef MenuCursor_hpp
#define MenuCursor_hpp

#include "cocos2d.h"
#include "BattleObject.hpp"

class BattleField;
class Creature;

class MenuCursor : public BattleObject
{
private:
    
    int _menuItemId;
    bool _isSelected;
    bool _isValid;
    
    std::string _menuImageFileValid;
    std::string _menuImageFileInvalid;
    
    
    void checkValid(BattleField * field, Creature * creature);
    Vec2 getEnterPosition(Vec2 pos);
    Vec2 getExitPosition(Vec2 pos);
    
public:
    
    MenuCursor(int menuItemId);
    
    bool isSelected();
    void setSelected(bool val);
    
    bool isValid();
    
    void sendToField(BattleField * field, Vec2 position);
    
    
};

#endif /* MenuCursor_hpp */
