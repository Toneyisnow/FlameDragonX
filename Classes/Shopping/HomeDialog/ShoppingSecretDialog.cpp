//
//  ShoppingSecretDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingSecretDialog.hpp"
#include "LocalizedStrings.hpp"

void ShoppingSecretDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(51);
    this->setMessage(message);
}

void ShoppingSecretDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(52);
    this->setMessage(message);
}

ShopType ShoppingSecretDialog::getShopType()
{
    return ShopType_Secret;
}
