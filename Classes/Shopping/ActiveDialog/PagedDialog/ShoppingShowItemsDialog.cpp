//
//  ShoppingShowItemsDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingShowItemsDialog.hpp"
#include "ShoppingLayer.hpp"
#include "DataStore.hpp"
#include "TouchableLabel.hpp"

ShoppingShowItemsDialog::ShoppingShowItemsDialog(Vector<FDNumber *> & itemList, int pageIndex, bool isSellPrice)
: ShoppingPagedDialog(pageIndex)
{
    _itemList = itemList;
    _isSellPrice = isSellPrice;
}

void ShoppingShowItemsDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingPagedDialog::showDialog(layer);
    
    // Show the items
    int startX = 25;
    int startY = 55;
    int intervalX = 150;
    int intervalY = 25;
    
    int startIndex = _pageIndex * this->getMaxPerPage();
    for (int i = 0; i + startIndex < this->getTotalCount() && i < this->getMaxPerPage(); i++) {
        
        int itemIndex = i + startIndex;
        int nowX = startX + intervalX * (i % 2);
        int nowY = startY - intervalY * (i / 2);
        
        int itemId = _itemList.at(itemIndex)->getValue();
        ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
        
        // Icon
        std::string iconFileName;
        if (item->isAttackItem())
        {
            iconFileName = "Others/ItemAttackIcon_0.png";
        }
        else if (item->isDefendItem())
        {
            iconFileName = "Others/ItemDefendIcon_0.png";
        }
        else
        {
            iconFileName = "Others/ItemUsableIcon_0.png";
        }
        
        TouchableSprite * iconSprite = TouchableSprite::create(iconFileName);
        iconSprite->setTag(itemIndex);
        iconSprite->setAnchorPoint(Vec2(0, 0));
        iconSprite->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowItemsDialog::clickedOnItem));
        _baseSprite->addChild(iconSprite, Vec2(nowX - 20, nowY));
        
        // Name
        TouchableLabel * nameLabel = TouchableLabel::createWithTTF(item->getName(), "fonts/mini_black.ttf", 10);
        nameLabel->setTag(itemIndex);
        nameLabel->setAnchorPoint(Vec2(0, 0));
        nameLabel->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowItemsDialog::clickedOnItem));
        _baseSprite->addChild(nameLabel, Vec2(nowX + 10, nowY));
        
        // Attribute
        TouchableLabel * attributeLabel = TouchableLabel::createWithTTF(item->getAttributeString(), "fonts/mini_black.ttf", 4.5);
        attributeLabel->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addChild(attributeLabel, Vec2(nowX + 80, nowY + 10));
        
        // Money
        int showPrice = _isSellPrice ? item->getSellPrice() : item->getPrice();
        std::string moneyString = StringUtils::format("$%05d", showPrice);
        TouchableLabel * moneyLabel = TouchableLabel::createWithTTF(moneyString, "fonts/mini_black.ttf", 4.5);
        moneyLabel->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addChild(moneyLabel, Vec2(nowX + 80, nowY));
        
    }
    
    
}

int ShoppingShowItemsDialog::getMaxPerPage()
{
    return 6;
}

int ShoppingShowItemsDialog::getTotalCount()
{
    return (int)_itemList.size();
}

void ShoppingShowItemsDialog::clickedOnItem(int index)
{
    _returnValue = index;
    this->closeDialog();
}
