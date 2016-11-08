//
//  ShoppingHomeDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingHomeDialog.hpp"
#include "ShoppingLayer.hpp"
#include "ShoppingShowFriendsDialog.hpp"
#include "CreatureData.hpp"
#include "ShoppingShowItemsDialog.hpp"
#include "ShoppingMessageDialog.hpp"
#include "ShoppingConfirmDialog.hpp"

#include "LocalizedStrings.hpp"
#include "DataStore.hpp"

using namespace std;

void ShoppingHomeDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingDialog::showDialog(layer);
    
    // Show the buttons
    this->generateButtons();
    
    int posX = _baseSprite->getContentSize().width - 60;
    int posY = 20;
    
    for (TouchableSprite * button : _buttons) {
        _baseSprite->addChild(button, Vec2(posX, posY));
        posX += 30;
    }
    
    _message = nullptr;
    initMessage();
}

void ShoppingHomeDialog::generateButtons()
{
    // Should be implemented in sub class
}

void ShoppingHomeDialog::initMessage()
{
    
}

void ShoppingHomeDialog::updateMessage()
{
    
}

void ShoppingHomeDialog::setMessage(std::string message)
{
    if (_message != nullptr) {
        
        _baseSprite->removeChild(_message, true);
        _message = nullptr;
    }
    
    _message = Label::createWithTTF(message.c_str(), "fonts/mini_black.ttf", DEFAULT_FONT_SIZE);
    _message->setColor(Color3B(255, 255, 255));
    _message->setAnchorPoint(Vec2(0, 0.5f));
    _baseSprite->addLabel(_message, MESSAGE_POSITION);

}


TouchableSprite * ShoppingHomeDialog::button_Buy(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Buy_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onBuy));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Sell(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Sell_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onSell));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_GiveItem(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Give_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onGive));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Equip(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Equip_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onEquip));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Info(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Info_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onInfo));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Save(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Save_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onSaveGame));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Load(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Load_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onLoadGame));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Revive(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Revive_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onRevive));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Transfer(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Trans_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onTransfer));
    return button;
}

TouchableSprite * ShoppingHomeDialog::button_Exit(){
    TouchableSprite* button = TouchableSprite::create("Others/Shop_Exit_0.png");
    button->setCallback(this, CALLBACK0_SELECTOR(ShoppingHomeDialog::onExitGame));
    return button;
}


void ShoppingHomeDialog::onBuy(){
    
}

void ShoppingHomeDialog::onSell(){
    
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_SelectedFriend));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingHomeDialog::onGive(){
    
}

void ShoppingHomeDialog::onInfo(){
    
}

void ShoppingHomeDialog::onSaveGame(){
    
}

void ShoppingHomeDialog::onLoadGame(){
    
}

void ShoppingHomeDialog::onExitGame(){
    
}

void ShoppingHomeDialog::onEquip(){
    
}

void ShoppingHomeDialog::onRevive(){
    
}

void ShoppingHomeDialog::onTransfer(){
    
}


void ShoppingHomeDialog::onSell_SelectedFriend(int index){
    
    if (index == -1)
    {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(index);
    
    if (record->creatureData()->isItemEmpty()) {
        
        // Error Message: There is no item
        ShoppingMessageDialog * message = new ShoppingMessageDialog(LocalizedStrings::getInstance()->getConfirmString(64).c_str());
        message->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_Reset));
        message->showDialog(_layer);
        message->release();
        return;
    }
    else
    {
        Vector<FDNumber *> itemList = *(record->creatureData()->itemList);
    
        _lastPageIndex = 0;
        ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(itemList, 0, false);
        itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_SelectedItem));
        itemDialog->showDialog(_layer);
        itemDialog->release();
    }
}

void ShoppingHomeDialog::onSell_SelectedItem(int index){
    
    if (index == -1)
    {
        return;
    }
    
    if (index < 0) {
        
        Vector<FDNumber *> itemList = *(_chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex)->creatureData()->itemList);
        
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(itemList, _lastPageIndex, false);
        itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_SelectedItem));
        itemDialog->showDialog(_layer);
        itemDialog->release();
        return;
    }
    
    _lastSelectedItemIndex = index;
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    int itemId = record->creatureData()->itemList->at(index)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    
    std::string message = StringUtils::format(LocalizedStrings::getInstance()->getMessageString(55).c_str(), item->getName().c_str(), item->getPrice());
    
    // Confirm Message
    ShoppingConfirmDialog * confirm = new ShoppingConfirmDialog(message);
    confirm->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_Confirm));
    confirm->showDialog(_layer);
    confirm->release();
    return;
    
}

void ShoppingHomeDialog::onSell_Reset(int index)
{
    this->onSell();
}

void ShoppingHomeDialog::onSell_Confirm(int index) {
    
    if (index != 1)
    {
        // Cancel
        this->onSell_SelectedFriend(_lastSelectedCreatureIndex);
        return;
    }
    
    this->doSell();
}

void ShoppingHomeDialog::doSell() {
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    int itemId = record->creatureData()->itemList->at(_lastSelectedItemIndex)->getValue();
    ItemDefinition * item = DataStore::getInstance()->getItemDefinition(itemId);
    
    _chapterRecord->setMoney(_chapterRecord->getMoney() + item->getSellPrice());
    record->creatureData()->removeItem(_lastSelectedItemIndex);
    
    _layer->updateMoneyBar();
}

void ShoppingHomeDialog::onGive_Start(int index){
    
}

void ShoppingHomeDialog::onGive_SelectedWhose(int whoseIndex){
    
}

void ShoppingHomeDialog::onGive_SelectedItem(int itemIndex){
    
}

void ShoppingHomeDialog::onGive_Whom(int index){
    
}

void ShoppingHomeDialog::onGive_SelectedWhom(int whomIndex){
    
}

void ShoppingHomeDialog::doGive(int creatureIndex){
    
}


void ShoppingHomeDialog::onInfo_ShowItems(int index){
    
}

void ShoppingHomeDialog::onInfo_ShowMagics(int index){
    
}
