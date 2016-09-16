//
//  SelectableBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "SelectableBox.hpp"

SelectableBox::SelectableBox()
{
    _baseSprite = Sprite::create("Others/ContainerBase.png");

}

Sprite * SelectableBox::getSprite()
{
    return _baseSprite;
}
