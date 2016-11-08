//
//  ShoppingActiveDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/5/16.
//
//

#include "ShoppingActiveDialog.hpp"
#include "ShoppingLayer.hpp"

void ShoppingActiveDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingDialog::showDialog(layer);
    layer->setActiveDialog(this);
}
