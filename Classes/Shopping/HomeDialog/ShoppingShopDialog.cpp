//
//  ShoppingShopDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingShopDialog.hpp"
#include "ShoppingShowItemsDialog.hpp"
#include "DataStore.hpp"
#include "LocalizedStrings.hpp"
#include "ShoppingConfirmDialog.hpp"

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
    this->showActiveDialog(itemDialog);
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
        this->showActiveDialog(itemDialog);
        itemDialog->release();
        return;
    }
    
    log("onBuy_Selected index=%d", index);
    Vector<FDNumber *> shopItemList = this->getShopItemList();
    _lastSelectedItemIndex = shopItemList.at(index)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(_lastSelectedItemIndex);
    
    // Confirm Message
    std::string confirmString = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(54).c_str(), item->getName().c_str(), item->getAttributeString().c_str());
    
    ShoppingConfirmDialog * confirm = new ShoppingConfirmDialog(confirmString);
    confirm->setCallback(this, CALLBACK1_SELECTOR(ShoppingShopDialog::onBuy_Confirmed));
    this->showActiveDialog(confirm);
    confirm->release();
    
}

void ShoppingShopDialog::onBuy_Confirmed(int index)
{
    if (index == 1) {
        log("Confirmed Buy the item.");
    }
}

void ShoppingShopDialog::onBuyAmor_SelectedTarget(int index)
{
    
}

void ShoppingShopDialog::onBuyAmor_Done(int index)
{
    
}

void ShoppingShopDialog::doBuyItem(bool equip)
{
    
}

void ShoppingShopDialog::onBuyItem_Done(int index)
{
    
}
