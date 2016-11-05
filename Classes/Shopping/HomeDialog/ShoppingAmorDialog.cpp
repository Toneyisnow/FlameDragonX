//
//  ShoppingAmorDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingAmorDialog.hpp"
#include "LocalizedStrings.hpp"

void ShoppingAmorDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(51);
    this->setMessage(message);
}

void ShoppingAmorDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(52);
    this->setMessage(message);
}

ShopType ShoppingAmorDialog::getShopType()
{
    return ShopType_Amor;
}
