//
//  ShoppingChurchDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingChurchDialog.hpp"
#include "LocalizedStrings.hpp"

void ShoppingChurchDialog::generateButtons()
{
    _buttons.pushBack(this->button_Info());
    _buttons.pushBack(this->button_GiveItem());
    _buttons.pushBack(this->button_Revive());
    _buttons.pushBack(this->button_Transfer());
}

void ShoppingChurchDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(55);
    this->setMessage(message);
}

void ShoppingChurchDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(56);
    this->setMessage(message);
}
