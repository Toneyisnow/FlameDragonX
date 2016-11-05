//
//  ShoppingBarDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingBarDialog.hpp"
#include "LocalizedStrings.hpp"

void ShoppingBarDialog::generateButtons()
{
    _buttons.pushBack(this->button_Info());
    _buttons.pushBack(this->button_Save());
    _buttons.pushBack(this->button_Load());
    _buttons.pushBack(this->button_Exit());
}

void ShoppingBarDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(55);
    this->setMessage(message);
}

void ShoppingBarDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(56);
    this->setMessage(message);
}
