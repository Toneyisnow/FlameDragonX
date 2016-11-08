//
//  ShoppingMessageDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingMessageDialog_hpp
#define ShoppingMessageDialog_hpp

#include "ShoppingActiveDialog.hpp"

class ShoppingMessageDialog : public ShoppingActiveDialog
{
private:
    
    std::string _message;
    
    
public:
    
    ShoppingMessageDialog(std::string message);
    virtual void showDialog(ShoppingLayer * layer) override;
    
};

#endif /* ShoppingMessageDialog_hpp */
