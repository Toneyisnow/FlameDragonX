//
//  ShoppingSelectAmorTargetDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingSelectAmorTargetDialog_hpp
#define ShoppingSelectAmorTargetDialog_hpp

#include "ShoppingPagedDialog.hpp"
#include "CreatureRecord.hpp"
#include "FDNumber.hpp"

class ShoppingSelectAmorTargetDialog : public ShoppingPagedDialog
{
private:
    
    Vector<CreatureRecord *> _allCreatureRecords;
    Vector<FDNumber *> _selectedCreatures;
    int _itemId;
    
public:
    
    ShoppingSelectAmorTargetDialog(Vector<CreatureRecord *> creatureRecords, int itemId, int pageIndex);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    void onClicked(int index);
    
    virtual int getMaxPerPage() override;
    virtual int getTotalCount() override;
};


#endif /* ShoppingSelectAmorTargetDialog_hpp */
