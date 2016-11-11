//
//  ShoppingHomeDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingHomeDialog_hpp
#define ShoppingHomeDialog_hpp

#include "cocos2d.h"
#include "ShoppingDialog.hpp"
#include "TouchableSprite.hpp"

class ShoppingHomeDialog : public ShoppingDialog
{
protected:
    
    int _lastSelectedItemIndex;
    int _lastSelectedItemId;
    int _lastSelectedCreatureIndex;
    int _lastPageIndex;
    
    Label * _message;
    
    Vector<TouchableSprite *> _buttons;
    
public:
    
    /// ShoppingHomeDialog(ChapterRecord * record);
    
    virtual void showDialog(ShoppingLayer * layer) override;
    
    virtual void initMessage();
    virtual void updateMessage();
    void setMessage(std::string message);
    
    virtual void generateButtons();
    
    TouchableSprite * button_Buy();
    TouchableSprite * button_Sell();
    TouchableSprite * button_GiveItem();
    TouchableSprite * button_Equip();
    TouchableSprite * button_Info();
    TouchableSprite * button_Save();
    TouchableSprite * button_Load();
    TouchableSprite * button_Revive();
    TouchableSprite * button_Transfer();
    TouchableSprite * button_Exit();
    
    virtual void onBuy();
    virtual void onSell();
    virtual void onGive();
    virtual void onInfo();
    virtual void onSaveGame();
    virtual void onLoadGame();
    virtual void onExitGame();
    virtual void onEquip();
    virtual void onRevive();
    virtual void onTransfer();
    
    void onSell_SelectedFriend(int friendIndex);
    void onSell_SelectedItem(int itemIndex);
    void onSell_Reset(int index);
    void onSell_Confirm(int index);
    void doSell();
    
    void onGive_Start(int index);
    void onGive_SelectedWhose(int whoseIndex);
    void onGive_SelectedItem(int itemIndex);
    void onGive_Whom(int index);
    void onGive_SelectedWhom(int whomIndex);
    void doGive(int creatureIndex);
    
    void onEquip_SelectedFriend(int index);
    void onEquip_SelectedItem(int index);
    void doEquip();
    
    void onInfo_ShowItems(int index);
    void onInfo_ShowMagics(int index);
    void onInfo_Close(int index);
};

#endif /* ShoppingHomeDialog_hpp */
