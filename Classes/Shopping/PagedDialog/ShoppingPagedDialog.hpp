//
//  ShoppingPagedDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingPagedDialog_hpp
#define ShoppingPagedDialog_hpp

#include "ShoppingDialog.hpp"

class ShoppingPagedDialog : public ShoppingDialog
{
protected:
    
    int _pageIndex;
    
    void clickedDown();
    void clickedUp();
    
public:
    
    ShoppingPagedDialog(int index);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    virtual int getMaxPerPage();
    virtual int getTotalCount();
    
};

#endif /* ShoppingPagedDialog_hpp */
