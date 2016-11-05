//
//  ShoppingShowItemsDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingShowItemsDialog_hpp
#define ShoppingShowItemsDialog_hpp

#include "ShoppingPagedDialog.hpp"
#include "FDNumber.hpp"

class ShoppingShowItemsDialog : public ShoppingPagedDialog
{
private:
    
    Vector<FDNumber *> _itemList;
    bool _isSellPrice;
    
    void clickedOnItem(int index);
    
public:
    
    ShoppingShowItemsDialog(Vector<FDNumber *> & itemList, int pageIndex, bool isSellPrice);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    virtual int getMaxPerPage() override;
    virtual int getTotalCount() override;
    
};



#endif /* ShoppingShowItemsDialog_hpp */
