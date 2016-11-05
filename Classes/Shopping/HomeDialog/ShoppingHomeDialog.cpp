//
//  ShoppingHomeDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingHomeDialog.hpp"
#include "ShoppingLayer.hpp"

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

void ShoppingHomeDialog::showActiveDialog(ShoppingDialog * dialog)
{
    dialog->showDialog(_layer);
    _layer->setActiveDialog(dialog);
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


void ShoppingHomeDialog::onSell_SelectedFriend(int friendIndex){
    
}

void ShoppingHomeDialog::onSell_SelectedItem(int itemIndex){
    
}

void ShoppingHomeDialog::onSell_Confirm(int index){
    
}

void ShoppingHomeDialog::doSell(){
    
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
