//
//  DatoBar.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "DatoBar.hpp"

DatoBar::DatoBar(int creatureAniId)
{
    
    _baseSprite = Sprite::create("Others/CreatureDato.png");
}

Sprite * DatoBar::getSprite()
{
    return _baseSprite;
}
