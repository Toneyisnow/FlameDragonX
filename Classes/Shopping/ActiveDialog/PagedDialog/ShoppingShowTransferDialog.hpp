//
//  ShoppingShowTransferDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingShowTransferDialog_hpp
#define ShoppingShowTransferDialog_hpp

#include "cocos2d.h"
#include "ShoppingPagedDialog.hpp"
#include "TransferDefinition.hpp"
#include "CreatureRecord.hpp"

USING_NS_CC;

class ShoppingShowTransferDialog : public ShoppingPagedDialog
{
private:
    
    Vector<TransferDefinition *> _transferList;
    
public:
    
    ShoppingShowTransferDialog(Vector<CreatureRecord *> &creatures, int pageIndex);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    virtual int getMaxPerPage() override;
    virtual int getTotalCount() override;
    
    void onClicked(int transferId);
};

#endif /* ShoppingShowTransferDialog_hpp */
