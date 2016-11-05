//
//  ShoppingItemDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingItemDialog.hpp"
#include "LocalizedStrings.hpp"

void ShoppingItemDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(53);
    this->setMessage(message);
}

void ShoppingItemDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(54);
    this->setMessage(message);
}

ShopType ShoppingItemDialog::getShopType()
{
    return ShopType_Item;
}
