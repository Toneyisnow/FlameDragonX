//
//  ShoppingItemDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingItemDialog_hpp
#define ShoppingItemDialog_hpp

#include "cocos2d.h"
#include "ShoppingShopDialog.hpp"

class ShoppingItemDialog : public ShoppingShopDialog
{
private:
    
public:
    
    virtual void initMessage() override;
    virtual void updateMessage() override;
    virtual ShopType getShopType() override;

};

#endif /* ShoppingItemDialog_hpp */
