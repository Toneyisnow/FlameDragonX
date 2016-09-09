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
class FDActivity;

class MenuCursor : public BattleObject
{
private:
    
    int _menuItemId;
    bool _isSelected;
    bool _isValid;
    
    Vec2 _centerPosition;
    Vec2 _cursorPosition;
    
    std::string _menuImageFileValid;
    std::string _menuImageFileInvalid;
    
    BattleField * _field;
    
    Vec2 getCursorPosition(Vec2 pos);
    
public:
    
    MenuCursor(int menuItemId, BattleField * field, Vec2 position);
    
    void checkValidation(Creature * creature);
    
    bool isSelected();
    void setSelected(bool val);
    
    bool isValid();
    
    void sendToField(BattleField * field, Vec2 position);
    
    FDActivity * onOpenActivity();
    FDActivity * onRemovalActivity() override;
};

#endif /* MenuCursor_hpp */
