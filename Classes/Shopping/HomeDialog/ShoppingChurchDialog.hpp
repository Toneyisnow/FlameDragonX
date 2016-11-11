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
    
    virtual void onRevive() override;
    void onRevive_SelectedFriend(int index);
    void onRevive_Confirmed(int index);
    void doRevive();
    
    virtual void onTransfer() override;
    void onTransfer_SelectedFriend(int index);
    void onTransfer_Confirm(int index);
    void doTransfer();
    
    
};

#endif /* ShoppingChurchDialog_hpp */
