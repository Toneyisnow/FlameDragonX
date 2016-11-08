//
//  ShoppingSelectAmorTargetDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingSelectAmorTargetDialog.hpp"
#include "DataStore.hpp"
#include "TouchableSprite.hpp"
#include "TouchableLabel.hpp"

USING_NS_CC;
using namespace std;

ShoppingSelectAmorTargetDialog::ShoppingSelectAmorTargetDialog(Vector<CreatureRecord *> creatureRecords, int itemId, int pageIndex)
: ShoppingPagedDialog(pageIndex)
{
    _allCreatureRecords = creatureRecords;
    _itemId = itemId;
    
    int index = 0;
    for (CreatureRecord * creature : creatureRecords) {
        CreatureDefinition * creatureDef = DataStore::getInstance()->getCreatureDefinition(creature->definitionId);
        if (creatureDef->canEquip(itemId)) {
            _selectedCreatures.pushBack(FDNumber::numberWithInt(index));
        }
        index ++;
    }
    
}

void ShoppingSelectAmorTargetDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingPagedDialog::showDialog(layer);

    int startX = 15;
    int startY = 58;
    int intervalY = 26;
    
    int startIndex = _pageIndex * this->getMaxPerPage();
    for (int i = 0; i + startIndex < _selectedCreatures.size() && i < this->getMaxPerPage(); i++) {
        
        int creatureIndex = _selectedCreatures.at(i + startIndex)->getValue();
        CreatureRecord * record = _allCreatureRecords.at(creatureIndex);
        CreatureDefinition * def = DataStore::getInstance()->getCreatureDefinition(record->definitionId);
    
        // Icon
        TouchableSprite * iconSprite = TouchableSprite::create(StringUtils::format("Icons/Icon-%03d-02.png", def->animationId));
        iconSprite->setTag(creatureIndex);
        iconSprite->setCallback(this, CALLBACK1_SELECTOR(ShoppingSelectAmorTargetDialog::onClicked));
        iconSprite->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addChild(iconSprite, Vec2(startX, startY - intervalY * i));
        
        // Name
        TouchableLabel * nameLabel = TouchableLabel::createWithTTF(def->name, "fonts/mini_black.ttf", 14);
        nameLabel->setTag(creatureIndex);
        nameLabel->setCallback(this, CALLBACK1_SELECTOR(ShoppingSelectAmorTargetDialog::onClicked));
        nameLabel->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addLabel(nameLabel, Vec2(startX + 25, startY - intervalY * i));
        
        // AP
        std::string ap = StringUtils::format("AP %03d -> %03d", record->creatureData()->calculatedAp(), record->creatureData()->calculatedApWithItem(_itemId));
        Label * apLabel = Label::createWithTTF(ap.c_str(), "fonts/mini_black.ttf", 9);
        _baseSprite->addLabel(apLabel, Vec2(startX + 80, startY - intervalY * i + 10));
        
        // DP
        std::string dp = StringUtils::format("DP %03d -> %03d", record->creatureData()->calculatedDp(), record->creatureData()->calculatedDpWithItem(_itemId));
        Label * dpLabel = Label::createWithTTF(dp.c_str(), "fonts/mini_black.ttf", 9);
        _baseSprite->addLabel(dpLabel, Vec2(startX + 80, startY - intervalY * i));
        
        // HIT
        std::string hit = StringUtils::format("HIT %03d -> %03d", record->creatureData()->calculatedHit(), record->creatureData()->calculatedHitWithItem(_itemId));
        Label * hitLabel = Label::createWithTTF(hit.c_str(), "fonts/mini_black.ttf", 9);
        _baseSprite->addLabel(hitLabel, Vec2(startX + 150, startY - intervalY * i + 10));
        
        // EV
        std::string ev = StringUtils::format("EV %03d -> %03d", record->creatureData()->calculatedEv(), record->creatureData()->calculatedEvWithItem(_itemId));
        Label * evLabel = Label::createWithTTF(ev.c_str(), "fonts/mini_black.ttf", 9);
        _baseSprite->addLabel(evLabel, Vec2(startX + 150, startY - intervalY * i));
    }

}

void ShoppingSelectAmorTargetDialog::onClicked(int index)
{
    _returnValue = index;
    this->closeDialog();
}

int ShoppingSelectAmorTargetDialog::getMaxPerPage()
{
    return 3;
}

int ShoppingSelectAmorTargetDialog::getTotalCount()
{
    return (int)_selectedCreatures.size();
}
