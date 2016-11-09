//
//  ShoppingShowFriendsDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#ifndef ShoppingShowFriendsDialog_hpp
#define ShoppingShowFriendsDialog_hpp

#include "ShoppingPagedDialog.hpp"

class ShoppingShowFriendsDialog : public ShoppingPagedDialog
{
private:
    
    Vector<CreatureRecord *> _allCreatureRecords;
    Vector<FDNumber *> _selectedCreatures;
    
public:
    
    ShoppingShowFriendsDialog(Vector<CreatureRecord *> &allCreatureRecords, int pageIndex);
    ShoppingShowFriendsDialog(Vector<CreatureRecord *> &allCreatureRecords, bool showDeadOnly, int pageIndex);
    
    void onClicked(int index);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    virtual int getMaxPerPage() override;
    virtual int getTotalCount() override;
};


#endif /* ShoppingShowFriendsDialog_hpp */
