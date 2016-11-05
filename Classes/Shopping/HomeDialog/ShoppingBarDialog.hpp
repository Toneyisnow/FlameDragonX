//
//  ShoppingBarDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingBarDialog_hpp
#define ShoppingBarDialog_hpp


#include "cocos2d.h"
#include "ShoppingHomeDialog.hpp"

class ShoppingBarDialog : public ShoppingHomeDialog
{
private:
    
public:
    
    virtual void initMessage() override;
    virtual void updateMessage() override;
    
    void generateButtons() override;

};

#endif /* ShoppingBarDialog_hpp */
