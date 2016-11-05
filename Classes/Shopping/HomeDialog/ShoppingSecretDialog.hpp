//
//  ShoppingSecretDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingSecretDialog_hpp
#define ShoppingSecretDialog_hpp

#include "cocos2d.h"
#include "ShoppingShopDialog.hpp"

class ShoppingSecretDialog : public ShoppingShopDialog
{
private:
    
public:
    
    virtual void initMessage() override;
    virtual void updateMessage() override;
    virtual ShopType getShopType() override;

};

#endif /* ShoppingSecretDialog_hpp */
