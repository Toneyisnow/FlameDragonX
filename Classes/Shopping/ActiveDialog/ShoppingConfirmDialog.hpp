//
//  ShoppingConfirmDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingConfirmDialog_hpp
#define ShoppingConfirmDialog_hpp

#include "ShoppingActiveDialog.hpp"

class ShoppingConfirmDialog : public ShoppingActiveDialog
{
private:
    
    std::string _message;
    
    void onClickedYes();
    void onClickedNo();
    
public:
    
    ShoppingConfirmDialog(std::string message);
    virtual void showDialog(ShoppingLayer * layer) override;
    
    
};

#endif /* ShoppingConfirmDialog_hpp */
