//
//  ItemBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "ItemBox.hpp"
#include "DataStore.hpp"
#include "TouchableSprite.hpp"
#include "TouchableLabel.hpp"

ItemBox::ItemBox(Creature * creature, MessageBoxOperatingType type, Ref* caller, SEL_CALLBACK1 method)
: SelectableBox(creature, type, caller, method)
{
    
    /*
    Vector<FDNumber *> itemList = *(creature->creatureData()->itemList);
    for (int i = 0; i < itemList.size(); i++) {
        
        int locationX = 150 * (i / 4) + 25;
        int locationY = 73 - 22 * (i % 4);
        
        int itemId = itemList.at(i)->getValue();
        ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
        
        bool itemInUse = (creature->creatureData()->attackItemIndex == i) || (creature->creatureData()->defendItemIndex == i);
        
        std::string iconFileName;
        if (item->isAttackItem()) {
            iconFileName = StringUtils::format("Others/ItemAttackIcon_%d.png", itemInUse);
        }
        else if (item->isDefendItem()) {
            iconFileName = StringUtils::format("Others/ItemDefendIcon_%d.png", itemInUse);
        }
        else {
            iconFileName = "Others/ItemUsableIcon_0.png";
        }
        
        TouchableSprite * iconSprite = TouchableSprite::create(iconFileName);
        iconSprite->setAnchorPoint(Vec2(0, 0));
        iconSprite->setTag(i);
        iconSprite->setCallback(caller , method);
        _baseSprite->addChild(iconSprite, Vec2(locationX - 20, locationY));
        
        // Name
        TouchableLabel * nameLabel = TouchableLabel::createWithTTF(item->getName(), "fonts/mini_black.ttf", 14);
        nameLabel->setAnchorPoint(Vec2(0, 0));
        nameLabel->setTag(i);
        nameLabel->setCallback(caller, method);
        _baseSprite->addLabel(nameLabel, Vec2(locationX + 10, locationY));
        
        // Attribute
        TouchableLabel * attribute = TouchableLabel::createWithTTF(item->getAttributeString(), "fonts/mini_black.ttf", 12);
        attribute->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addLabel(attribute, Vec2(locationX + 80, locationY));
    }*/
    
    
}

