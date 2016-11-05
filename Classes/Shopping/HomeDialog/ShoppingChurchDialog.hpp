//
//  ShoppingChurchDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingChurchDialog_hpp
#define ShoppingChurchDialog_hpp


#include "cocos2d.h"
#include "ShoppingHomeDialog.hpp"

class ShoppingChurchDialog : public ShoppingHomeDialog
{
private:
    
public:
    
    virtual void initMessage() override;
    virtual void updateMessage() override;
    
    void generateButtons() override;
    
};

#endif /* ShoppingChurchDialog_hpp */
