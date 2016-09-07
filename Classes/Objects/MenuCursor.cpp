//
//  MenuCursor.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/6/16.
//
//

#include "MenuCursor.hpp"
#include "BattleField.hpp"
#include "Creature.hpp"
#include "SimpleMoveActivity.hpp"
#include "BattleScene.hpp"
#include "StringUtil.hpp"
#include "AnimationLibrary.hpp"

MenuCursor::MenuCursor(int menuItemId)
: BattleObject(BattleObject_Menu)
{
    _menuItemId = menuItemId;
    _isSelected = false;
    _isValid = true;
    
    _menuImageFileValid = StringUtil::format("Menu/Menu-%03d-1.png");
    _menuImageFileInvalid = StringUtil::format("Menu/Menu-%03d-3.png");
    initialize(_menuImageFileValid);
}

bool MenuCursor::isSelected()
{
    return _isSelected;
}

void MenuCursor::setSelected(bool val)
{
    _isSelected = val;
    
    if (_isSelected)
    {
        SlideAnimation * animation = AnimationLibrary::getInstance()->getMenuAnimation(_menuItemId);
        _animator->setAnimation(animation);
    }
    else
    {
        _animator->setAnimation(nullptr);
    }
}

bool MenuCursor::isValid()
{
    return _isValid;
}

void MenuCursor::sendToField(BattleField * field, Vec2 position)
{
    Creature * creature = field->getCreatureAt(position.x, position.y);
    
    checkValid(field, creature);
    
    field->addObject(this, position);
    
    SimpleMoveActivity * move = new SimpleMoveActivity(field, this, getEnterPosition(position), Constants::MENU_MOVE_SPEED);
    field->getBattleScene()->getActivityQueue()->insertSingleActivity(move);
    move->release();
}

Vec2 MenuCursor::getEnterPosition(Vec2 pos)
{
    int positionType = _menuItemId % 10;
    switch (positionType) {
        case 0:
            return Vec2(pos.x - 1, pos.y);
            break;
        case 1:
            return Vec2(pos.x, pos.y - 1);
            break;
        case 2:
            return Vec2(pos.x + 1, pos.y);
            break;
        case 3:
            return Vec2(pos.x, pos.y + 1);
            break;
            
        default:
            break;
    }
    
    return pos;
}

Vec2 MenuCursor::getExitPosition(Vec2 pos)
{
    int positionType = _menuItemId % 10;
    switch (positionType) {
        case 0:
            return Vec2(pos.x + 1, pos.y);
            break;
        case 1:
            return Vec2(pos.x, pos.y + 1);
            break;
        case 2:
            return Vec2(pos.x - 1, pos.y);
            break;
        case 3:
            return Vec2(pos.x, pos.y - 1);
            break;
            
        default:
            break;
    }
    
    return pos;
}


void MenuCursor::checkValid(BattleField * field, Creature * creature)
{
    if ((_menuItemId / 10 == 1 || _menuItemId / 10 ==2) && creature == nullptr)
    {
        // Error Creature is null
        return;
    }
    
    _isValid = true;
    switch (_menuItemId) {
        case 10:
            // Magic
            break;
            
        case 30:
            // Match
            _isValid = false;
            break;
        default:
            break;
    }
    
    
    if (_isValid)
    {
        _baseSprite->setTexture(_menuImageFileValid);
    }
    else
    {
        _baseSprite->setTexture(_menuImageFileInvalid);
    }
}
