//
//  MagicBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "MagicBox.hpp"
#include "DataStore.hpp"
#include "TouchableLabel.hpp"

MagicBox::MagicBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method)
: SelectableBox(creature, type, caller, method)
{
    Vector<FDNumber *> magicList = *(creature->creatureData()->magicList);
    for (int i = 0; i < magicList.size(); i++) {
        
        int locationX = 100 * (i / 4) + 10;
        int locationY = 73 - 22 * (i % 4);
        
        int magicId = magicList.at(i)->getValue();
        MagicDefinition * magic = DataStore::getInstance()->getMagicDefinition(magicId);
        
        // Name
        TouchableLabel * nameLabel = TouchableLabel::createWithTTF(magic->getName(), "fonts/mini_black.ttf", 14);
        nameLabel->setAnchorPoint(Vec2(0, 0));
        nameLabel->setTag(i);
        nameLabel->setCallback(caller, method);
        _baseSprite->addLabel(nameLabel, Vec2(locationX, locationY));
        
        // Attribute
        std::string mpCost = StringUtils::format("-MP %02d", magic->mpCost());
        TouchableLabel * attribute = TouchableLabel::createWithTTF(mpCost, "fonts/mini_black.ttf", 12);
        attribute->setAnchorPoint(Vec2(0, 0));
        attribute->setTag(i);
        attribute->setCallback(caller, method);
        _baseSprite->addLabel(attribute, Vec2(locationX + 50, locationY));
    }
    
}

