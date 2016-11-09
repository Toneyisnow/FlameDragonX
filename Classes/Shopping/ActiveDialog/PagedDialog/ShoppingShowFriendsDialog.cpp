//
//  ShoppingShowFriendsDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingShowFriendsDialog.hpp"
#include "TouchableSprite.hpp"
#include "TouchableLabel.hpp"
#include "DataStore.hpp"

ShoppingShowFriendsDialog::ShoppingShowFriendsDialog(Vector<CreatureRecord *> &allCreatureRecords, int pageIndex)
: ShoppingShowFriendsDialog(allCreatureRecords, false, pageIndex)
{
    
}
ShoppingShowFriendsDialog::ShoppingShowFriendsDialog(Vector<CreatureRecord *> &allCreatureRecords, bool showDeadOnly, int pageIndex)
: ShoppingPagedDialog(pageIndex)
{
    _allCreatureRecords = allCreatureRecords;
    _selectedCreatures.clear();
    
    int index = 0;
    for (CreatureRecord * creature : _allCreatureRecords) {
        if (!showDeadOnly || creature->creatureData()->hpCurrent <= 0) {
            _selectedCreatures.pushBack(FDNumber::numberWithInt(index));
        }
        index++;
    }
}

void ShoppingShowFriendsDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingPagedDialog::showDialog(layer);
    
    int startX = 10;
    int startY = 50;
    int intervalX = 100;
    int intervalY = 28;
    
    int startIndex = _pageIndex * this->getMaxPerPage();
    
    for (int i = 0; i + startIndex < _selectedCreatures.size() && i < this->getMaxPerPage(); i++) {
        
        int creatureIndex = _selectedCreatures.at(i + startIndex)->getValue();
        CreatureRecord * record = _allCreatureRecords.at(creatureIndex);
        CreatureDefinition * def = DataStore::getInstance()->getCreatureDefinition(record->definitionId);
        
        // Icon
        TouchableSprite * iconSprite = TouchableSprite::create(StringUtils::format("Icons/%03d/Icon-%03d-02.png", def->animationId, def->animationId));
        iconSprite->setTag(creatureIndex);
        iconSprite->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowFriendsDialog::onClicked));
        iconSprite->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addChild(iconSprite, Vec2(startX + intervalX * (i % 3), startY - intervalY * (i / 3)));
        
        // Name
        TouchableLabel * nameLabel = TouchableLabel::createWithTTF(def->name, "fonts/mini_black.ttf", 14);
        nameLabel->setTag(creatureIndex);
        nameLabel->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowFriendsDialog::onClicked));
        nameLabel->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addLabel(nameLabel, Vec2(startX + intervalX * (i % 3) + 25, startY - intervalY * (i / 3)));
    }
}

void ShoppingShowFriendsDialog::onClicked(int index)
{
    log("Clicked on Item %d", index);
    
    _returnValue = index;
    this->closeDialog();
}

int ShoppingShowFriendsDialog::getMaxPerPage()
{
    return 6;
}

int ShoppingShowFriendsDialog::getTotalCount()
{
    return (int)_selectedCreatures.size();
}
