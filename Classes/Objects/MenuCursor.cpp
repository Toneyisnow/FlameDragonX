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

MenuCursor::MenuCursor(int menuItemId, BattleField * field, Vec2 position)
: BattleObject(BattleObject_Menu)
{
    _menuItemId = menuItemId;
    _isSelected = false;
    _isValid = true;
    _field = field;
    
    _centerPosition = position;
    _cursorPosition = getCursorPosition(position);
    
    _menuImageFileValid = StringUtil::format("Menu/Menu-%03d-1.png", menuItemId);
    _menuImageFileInvalid = StringUtil::format("Menu/Menu-%03d-3.png", menuItemId);
    initialize(_menuImageFileValid);
}

int MenuCursor::getId()
{
    return _menuItemId;
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

FDActivity * MenuCursor::onOpenActivity()
{
    SimpleMoveActivity * move = new SimpleMoveActivity(_field, this, _cursorPosition, Constants::MENU_MOVE_SPEED);
    move->autorelease();
    
    return move;
}

FDActivity * MenuCursor::onRemovalActivity()
{
    if (_isRemoving) {
        return nullptr;
    }
    
    SimpleMoveActivity * move = new SimpleMoveActivity(_field, this, _centerPosition, Constants::MENU_MOVE_SPEED);
    move->autorelease();
    
    _isRemoving = true;
    return move;
}

Vec2 MenuCursor::getCursorPosition(Vec2 pos)
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

void MenuCursor::checkValidation(Creature * creature)
{
    if ((_menuItemId / 10 == 1 || _menuItemId / 10 == 2) && creature == nullptr)
    {
        // Error Creature is null
        return;
    }
    
    _isValid = true;
    switch (_menuItemId) {
        case 10:    // Magic
            _isValid = creature->canFireMagic();
            // Magic
            break;
        case 11:    // Attack
            _isValid = _field->searchTargetInAttackRange(creature).size() > 0;
            break;
        case 12:    // Item
            _isValid = creature->creatureData()->itemList->size() > 0;
            break;
        case 13:    // Waive Turn
            _isValid = true;
            break;
        case 20:    // Exchange Item
            _isValid = _field->hasAdjacentFriend(creature);
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
