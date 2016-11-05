//
//  ShoppingAmorDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingAmorDialog_hpp
#define ShoppingAmorDialog_hpp

#include "cocos2d.h"
#include "ShoppingShopDialog.hpp"

class ShoppingAmorDialog : public ShoppingShopDialog
{
private:
    
public:
    
    virtual void initMessage() override;
    virtual void updateMessage() override;
    virtual ShopType getShopType() override;
    
};

#endif /* ShoppingAmorDialog_hpp */
