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
#include "CompositeBox.hpp"

using namespace std;

void ShoppingHomeDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingDialog::showDialog(layer);
    
    // Show the buttons
    this->generateButtons();
    
    int posX = _baseSprite->getContentSize().width;
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
    
    this->updateMessage();
    
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onSell_SelectedFriend));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingHomeDialog::onGive(){
    
    log("onGive.");
    this->updateMessage();
    
    std::string message = LocalizedStrings::getInstance()->getMessageString(58);
    ShoppingMessageDialog * messageDialog = new ShoppingMessageDialog(message);
    messageDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_Start));
    messageDialog->showDialog(_layer);
    messageDialog->release();
}

void ShoppingHomeDialog::onInfo(){
    
    this->updateMessage();
    
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onInfo_ShowItems));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingHomeDialog::onSaveGame(){
    
}

void ShoppingHomeDialog::onLoadGame(){
    
}

void ShoppingHomeDialog::onExitGame(){
    
}

void ShoppingHomeDialog::onEquip(){
    
    _lastPageIndex = 0;
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onEquip_SelectedFriend));
    dialog->showDialog(_layer);
    dialog->release();
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
        ShoppingMessageDialog * message = new ShoppingMessageDialog(LocalizedStrings::getInstance()->getMessageString(64).c_str());
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
    
    std::string message = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(55).c_str(), item->getName().c_str(), item->getPrice());
    
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
    
    _lastPageIndex = 0;
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedWhose));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingHomeDialog::onGive_SelectedWhose(int index){
    
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedWhose));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(index);
    
    if (creature->creatureData()->isItemEmpty()) {
        
        // Error Message: There is no item
        ShoppingMessageDialog * message = new ShoppingMessageDialog(LocalizedStrings::getInstance()->getMessageString(64).c_str());
        message->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_Start));
        message->showDialog(_layer);
        message->release();
        return;
    }
    
    _lastPageIndex = 0;
    ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(*(creature->creatureData()->itemList), 0, false);
    itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedItem));
    itemDialog->showDialog(_layer);
    itemDialog->release();
}

void ShoppingHomeDialog::onGive_SelectedItem(int index){
    
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
        ShoppingShowItemsDialog * itemDialog = new ShoppingShowItemsDialog(*(creature->creatureData()->itemList), 0, false);
        itemDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedItem));
        itemDialog->showDialog(_layer);
        itemDialog->release();
        return;
    }
    
    _lastSelectedItemIndex = index;
    
    std::string message = LocalizedStrings::getInstance()->getMessageString(59);
    ShoppingMessageDialog * messageDialog = new ShoppingMessageDialog(message);
    messageDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_Whom));
    messageDialog->showDialog(_layer);
    messageDialog->release();
}

void ShoppingHomeDialog::onGive_Whom(int index){
    
    _lastPageIndex = 0;
    ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedWhom));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingHomeDialog::onGive_SelectedWhom(int index){
    
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_SelectedWhom));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    CreatureRecord * toCreature = _chapterRecord->getFriendRecordList().at(index);
    if (index != _lastSelectedCreatureIndex && toCreature->creatureData()->isItemFull()) {
        std::string message = LocalizedStrings::getInstance()->getMessageString(62);
        ShoppingMessageDialog * messageDialog = new ShoppingMessageDialog(message);
        messageDialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onGive_Whom));
        messageDialog->showDialog(_layer);
        messageDialog->release();
        return;
    }
    
    this->doGive(index);
    
    this->onGive();
}

void ShoppingHomeDialog::doGive(int creatureIndex){
    
    CreatureRecord * fromCreature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    CreatureRecord * toCreature = _chapterRecord->getFriendRecordList().at(creatureIndex);
    
    int itemId = fromCreature->creatureData()->getItem(_lastSelectedItemIndex)->getDefinitionId();
    
    fromCreature->creatureData()->removeItem(_lastSelectedItemIndex);
    toCreature->creatureData()->addItem(itemId);
}


void ShoppingHomeDialog::onEquip_SelectedFriend(int index){
    
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onEquip_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(index);
    Creature * creature = new Creature(record);
    CompositeBox * box = new CompositeBox(creature, MessageBoxType_Item, MessageBoxOperatingType_Equip);
    box->setReturnFunction(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onEquip_SelectedItem));
    box->showDialog(_layer);
    
    box->release();
    creature->release();
}

void ShoppingHomeDialog::onEquip_SelectedItem(int index)
{
    if (index == -1)
    {
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onEquip_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedItemIndex = index;
    
    this->doEquip();
    
    this->onEquip_SelectedFriend(_lastSelectedCreatureIndex);
}

void ShoppingHomeDialog::doEquip(){
    
    CreatureRecord * creature = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    ItemDefinition * item = creature->creatureData()->getItem(_lastSelectedItemIndex);
    CreatureDefinition * creatureDef = DataStore::getInstance()->getCreatureDefinition(creature->definitionId);
    
    if (!creatureDef->canEquip(item->getDefinitionId())) {
        return;
    }
    
    if (item->isAttackItem()) {
        creature->creatureData()->attackItemIndex = _lastSelectedItemIndex;
    } else if (item->isDefendItem()) {
        creature->creatureData()->defendItemIndex = _lastSelectedItemIndex;
    }
}

void ShoppingHomeDialog::onInfo_ShowItems(int index){
    
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onInfo_ShowItems));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(index);
    Creature * creature = new Creature(record);
    CompositeBox * box = new CompositeBox(creature, MessageBoxType_Item, MessageBoxOperatingType_ShowOnly);
    
    if (creature->knowMagic()) {
        box->setReturnFunction(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onInfo_ShowMagics));
    } else {
        box->setReturnFunction(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onInfo_Close));
    }
    
    box->showDialog(_layer);
    
    box->release();
    creature->release();
}

void ShoppingHomeDialog::onInfo_ShowMagics(int index){
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    Creature * creature = new Creature(record);
    CompositeBox * box = new CompositeBox(creature, MessageBoxType_Item, MessageBoxOperatingType_ShowOnly);
    
    box->setReturnFunction(this, CALLBACK1_SELECTOR(ShoppingHomeDialog::onInfo_Close));
    
    box->showDialog(_layer);
    
    box->release();
    creature->release();
}

void ShoppingHomeDialog::onInfo_Close(int index){
    
}
