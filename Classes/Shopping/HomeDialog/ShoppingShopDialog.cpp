//
//  ShoppingShopDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingShopDialog.hpp"
#include "ShoppingShowItemsDialog.hpp"
#include "ShoppingLayer.hpp"
#include "DataStore.hpp"
#include "LocalizedStrings.hpp"
#include "ShoppingConfirmDialog.hpp"
#include "ShoppingMessageDialog.hpp"
#include "ShoppingSelectAmorTargetDialog.hpp"
#include "ShoppingShowFriendsDialog.hpp"

void ShoppingShopDialog::generateButtons()
{
    _buttons.pushBack(this->button_Buy());
    _buttons.pushBack(this->button_Sell());
    _buttons.pushBack(this->button_Equip());
    _buttons.pushBack(this->button_GiveItem());
}

void ShoppingShopDialog::onBuy(){
    
    updateMessage();
    
    Vector<FDNumber *> shopItemList = this->getShopItemList();
    _lastPageIndex = 0;
    ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(shopItemList, 0, false);
    itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_Selected));
    itemDialog->showDialog(_layer);
    itemDialog->release();
}

Vector<FDNumber *> ShoppingShopDialog::getShopItemList()
{
    int chapterId = _chapterRecord->getChapterId();
    ShopDefinition * shop = DataStore::getInstance()->getShopDefinition(chapterId, this->getShopType());
    
    Vector<FDNumber *> result = shop->itemList();
    
    // Fix Bug: If the user doesn't have Item 805, here will add one for Chapter 11-22
    if (chapterId >= 11 && chapterId <= 22
        && this->getShopType() == ShopType_Item
        && _chapterRecord->getCreatureCarriesItem(805) != nullptr )
    {
        result.pushBack(FDNumber::numberWithInt(805));
    }
    
    // Fix Bug: If the user doesn't have Item 120, here will add one for Chapter 17-22
    if (chapterId >= 18 && chapterId <= 22
        && this->getShopType() == ShopType_Item
        && _chapterRecord->getCreatureCarriesItem(120) == nullptr)
    {
        result.pushBack(FDNumber::numberWithInt(120));
    }
    
    return result;
}

ShopType ShoppingShopDialog::getShopType()
{
    return ShopType_Item;
}

void ShoppingShopDialog::onBuy_Selected(int index)
{
    if (index == -1)
    {
        // Cancel
        return;
    }
    
    if (index < 0)
    {
        if (index == -2)
        {
            // Go Up Page
            _lastPageIndex --;
        }
    
        if (index == -3)
        {
            // Go Down Page
            _lastPageIndex ++;
        }
        
        Vector<FDNumber *> shopItemList = this->getShopItemList();
        ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(shopItemList, _lastPageIndex, false);
        itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_Selected));
        itemDialog->showDialog(_layer);
        itemDialog->release();
        return;
    }
    
    log("onBuy_Selected index=%d", index);
    Vector<FDNumber *> shopItemList = this->getShopItemList();
    _lastSelectedItemId = shopItemList.at(index)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(_lastSelectedItemId);
    
    // Confirm Message
    std::string confirmString = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(54).c_str(), item->getName().c_str(), item->getPrice());
    ShoppingConfirmDialog * confirm = new ShoppingConfirmDialog(confirmString);
    confirm->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_Confirmed));
    confirm->showDialog(_layer);
    confirm->release();
    
}

void ShoppingShopDialog::onBuy_Confirmed(int index)
{
    if (index != 1) {
        this->onBuy();
        return;
    }
    
    // Confirmed Buy
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(_lastSelectedItemId);
    if (_chapterRecord->getMoney() < item->getPrice()) {
        
        // Error Message: Not enough money
        ShoppingMessageDialog * message = new ShoppingMessageDialog(LocalizedStrings::getInstance()->getConfirmString(63).c_str());
        message->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_NotEnoughMoney));
        message->showDialog(_layer);
        message->release();
        return;
    }
    
    _lastPageIndex = 0;
    if (item->isDefendItem() || item->isAttackItem()) {
        ShoppingSelectAmorTargetDialog * dialog = new ShoppingSelectAmorTargetDialog(_chapterRecord->getFriendRecordList(), _lastSelectedItemId, 0);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuyAmor_SelectedTarget));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    else
    {
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), 0);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuyItem_SelectedTarget));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
}

void ShoppingShopDialog::onBuy_NotEnoughMoney(int index)
{
    this->onBuy();
}

void ShoppingShopDialog::onBuyAmor_SelectedTarget(int index)
{
    if (index == -1)
    {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingSelectAmorTargetDialog * dialog = new ShoppingSelectAmorTargetDialog(_chapterRecord->getFriendRecordList(), _lastSelectedItemId, _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuyAmor_SelectedTarget));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    
    // Check if the creature item bag is full
    CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    CreatureDefinition * creatureDef = DataStore::getInstance()->getCreatureDefinition(creature->creatureId);
    
    if (creature->creatureData()->isItemFull())
    {
        // Error Message: Item full
        std::string errorString = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(62).c_str(), creatureDef->name.c_str());
        ShoppingMessageDialog * message = new ShoppingMessageDialog(errorString);
        message->showDialog(_layer);
        message->release();
        return;
    }
    else
    {
        // Confirm Message
        ShoppingConfirmDialog * confirm = new ShoppingConfirmDialog(LocalizedStrings::getInstance()->getConfirmString(56).c_str());
        confirm->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_Confirmed));
        confirm->showDialog(_layer);
        confirm->release();
        return;
    }
}

void ShoppingShopDialog::onBuyAmor_ConfirmedEquip(int index)
{
    this->doBuyItem(index == 1);
}

void ShoppingShopDialog::onBuyItem_SelectedTarget(int index)
{
    if (index == -1)
    {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuyItem_SelectedTarget));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    
    // Check if the creature item bag is full
    CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    CreatureDefinition * creatureDef = DataStore::getInstance()->getCreatureDefinition(creature->creatureId);
    
    if (creature->creatureData()->isItemFull())
    {
        // Error Message: Item full
        std::string errorString = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(62).c_str(), creatureDef->name.c_str());
        ShoppingMessageDialog * message = new ShoppingMessageDialog(errorString);
        message->showDialog(_layer);
        message->release();
        return;
    }
    
    this->doBuyItem(false);
}

void ShoppingShopDialog::doBuyItem(bool equipIt)
{
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(_lastSelectedItemId);
    _chapterRecord->setMoney(_chapterRecord->getMoney() - item->getPrice());
    
    CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    creature->creatureData()->addItem(item->getDefinitionId());
    
    if (equipIt) {
        int itemIndex = (int)creature->creatureData()->itemList->size() - 1;
        if (item->isAttackItem())
        {
            creature->creatureData()->attackItemIndex = itemIndex;
        }
        else if (item->isDefendItem())
        {
            creature->creatureData()->defendItemIndex = itemIndex;
        }
    }
    
    _layer->updateMoneyBar();
}
