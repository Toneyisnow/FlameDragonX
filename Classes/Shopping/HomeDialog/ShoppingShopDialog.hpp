//
//  ShoppingShopDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingShopDialog_hpp
#define ShoppingShopDialog_hpp

#include "cocos2d.h"
#include "ShoppingHomeDialog.hpp"
#include "ShopDefinition.hpp"

class ShoppingShopDialog : public ShoppingHomeDialog
{
protected:

    Vector<FDNumber *> getShopItemList();

    
public:
    
    virtual void generateButtons() override;
    virtual ShopType getShopType();
    
    void onBuy() override;
    void onBuy_Selected(int index);
    void onBuy_Confirmed(int index);
    void onBuy_NotEnoughMoney(int index);
    
    void onBuyAmor_SelectedTarget(int index);
    void onBuyItem_SelectedTarget(int index);
    void onBuyAmor_ConfirmedEquip(int index);
    
    void doBuyItem(bool equip);
    
};

#endif /* ShoppingShopDialog_hpp */
