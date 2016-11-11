//
//  ShoppingChurchDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingChurchDialog.hpp"
#include "LocalizedStrings.hpp"
#include "ShoppingShowFriendsDialog.hpp"
#include "ShoppingMessageDialog.hpp"
#include "ShoppingConfirmDialog.hpp"
#include "ChapterRecord.hpp"
#include "GameFormula.hpp"
#include "ShoppingLayer.hpp"
#include "DataStore.hpp"
#include "ShoppingShowTransferDialog.hpp"
#include "FDRandom.hpp"

using namespace std;

void ShoppingChurchDialog::generateButtons()
{
    _buttons.pushBack(this->button_Info());
    _buttons.pushBack(this->button_GiveItem());
    _buttons.pushBack(this->button_Revive());
    _buttons.pushBack(this->button_Transfer());
}

void ShoppingChurchDialog::initMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(55);
    this->setMessage(message);
}

void ShoppingChurchDialog::updateMessage()
{
    std::string message = LocalizedStrings::getInstance()->getMessageString(56);
    this->setMessage(message);
}

void ShoppingChurchDialog::onRevive()
{
    this->updateMessage();
    
    bool hasDeadFriend = false;
    for (CreatureRecord * record : _chapterRecord->getFriendRecordList()) {
        if (record->creatureData()->hpCurrent <= 0) {
            hasDeadFriend = true;
            break;
        }
    }
    
    if (hasDeadFriend) {
        
        _lastPageIndex = 0;
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), true, _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onRevive_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
    }
    else {
        std::string message = LocalizedStrings::getInstance()->getMessageString(60);
        ShoppingMessageDialog * messageDialog = new ShoppingMessageDialog(message);
        messageDialog->showDialog(_layer);
        messageDialog->release();
    }
}

void ShoppingChurchDialog::onRevive_SelectedFriend(int index)
{
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), true, _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onRevive_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    _lastSelectedCreatureIndex = index;
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(index);
    int moneyNeeded = GameFormula::getMoneyNeededForRevive(record);
    
    std::string mtemplate = LocalizedStrings::getInstance()->getConfirmString(57);
    std::string message = StringUtils::format(mtemplate.c_str(), LocalizedStrings::getInstance()->getCreatureName(record->definitionId).c_str(), moneyNeeded);
    ShoppingConfirmDialog * dialog = new ShoppingConfirmDialog(message);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onRevive_Confirmed));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingChurchDialog::onRevive_Confirmed(int index)
{
    if (index < 0) {
        ShoppingShowFriendsDialog * dialog = new ShoppingShowFriendsDialog(_chapterRecord->getFriendRecordList(), true, _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onRevive_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    int moneyNeeded = GameFormula::getMoneyNeededForRevive(record);
    if (_chapterRecord->getMoney() < moneyNeeded) {
        std::string message = LocalizedStrings::getInstance()->getMessageString(63);
        ShoppingMessageDialog * dialog = new ShoppingMessageDialog(message);
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    this->doRevive();
}

void ShoppingChurchDialog::doRevive()
{
    CreatureRecord * record = _chapterRecord->getFriendRecordList().at(_lastSelectedCreatureIndex);
    int moneyNeeded = GameFormula::getMoneyNeededForRevive(record);
    
    record->creatureData()->hpCurrent = record->creatureData()->hpMax;
    _chapterRecord->setMoney(_chapterRecord->getMoney() - moneyNeeded);
    
    _layer->updateMoneyBar();
}


void ShoppingChurchDialog::onTransfer()
{
    this->updateMessage();
    
    bool hasTransferFriend = false;
    for (CreatureRecord * record : _chapterRecord->getFriendRecordList()) {
        if (record->creatureData()->level >= 20 && DataStore::getInstance()->getTransfersDefinition(record->definitionId) != nullptr) {
            hasTransferFriend = true;
            break;
        }
    }
    
    if (hasTransferFriend) {
        _lastPageIndex = 0;
        ShoppingShowTransferDialog * dialog = new ShoppingShowTransferDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onTransfer_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
    }
    else
    {
        std::string message = LocalizedStrings::getInstance()->getMessageString(61);
        ShoppingMessageDialog * dialog = new ShoppingMessageDialog(message);
        dialog->showDialog(_layer);
        dialog->release();
    }
}

void ShoppingChurchDialog::onTransfer_SelectedFriend(int index)
{
    if (index == -1) {
        return;
    }
    
    if (index < 0) {
        _lastPageIndex = (index == -2) ? _lastPageIndex - 1 : ((index == -3) ? _lastPageIndex + 1 : 0);
        ShoppingShowTransferDialog * dialog = new ShoppingShowTransferDialog(_chapterRecord->getFriendRecordList(), _lastPageIndex);
        dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onTransfer_SelectedFriend));
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    // Here the ID is the transferId
    _lastSelectedItemId = index;
    
    TransferDefinition * transfer = DataStore::getInstance()->getTransferDefinition(_lastSelectedItemId);
    CreatureDefinition * fromCreature = DataStore::getInstance()->getCreatureDefinition(transfer->fromCreatureDefId());
    CreatureDefinition * toCreature = DataStore::getInstance()->getCreatureDefinition(transfer->toCreatureDefId());
    std::string newOccupationName = toCreature->getOccupationName();
    int moneyNeeded = GameFormula::getDefaultTransferFee();
    
    std::string message = StringUtils::format(LocalizedStrings::getInstance()->getConfirmString(58).c_str(), fromCreature->name.c_str(), newOccupationName.c_str(), moneyNeeded);
    ShoppingConfirmDialog * dialog = new ShoppingConfirmDialog(message);
    dialog->setCallback(this, CALLBACK1_SELECTOR(ShoppingChurchDialog::onTransfer_Confirm));
    dialog->showDialog(_layer);
    dialog->release();
}

void ShoppingChurchDialog::onTransfer_Confirm(int index)
{
    if (index < 0) {
        this->onTransfer();
        return;
    }
    
    int moneyNeeded = GameFormula::getDefaultTransferFee();
    if (_chapterRecord->getMoney() < moneyNeeded) {
        std::string message = LocalizedStrings::getInstance()->getMessageString(63);
        ShoppingMessageDialog * dialog = new ShoppingMessageDialog(message);
        dialog->showDialog(_layer);
        dialog->release();
        return;
    }
    
    this->doTransfer();
}

void ShoppingChurchDialog::doTransfer()
{
    TransferDefinition * transfer = DataStore::getInstance()->getTransferDefinition(_lastSelectedItemId);
    CreatureDefinition * fromCreature = DataStore::getInstance()->getCreatureDefinition(transfer->fromCreatureDefId());
    CreatureDefinition * toCreature = DataStore::getInstance()->getCreatureDefinition(transfer->toCreatureDefId());
    
    CreatureRecord * creature = nullptr;
    for (CreatureRecord * record : _chapterRecord->getFriendRecordList()) {
        if (record->definitionId == transfer->fromCreatureDefId()) {
            creature = record;
            break;
        }
    }
    
    if (creature == nullptr) {
        return;
    }
    
    if (transfer->requireItemId() != 0) {
        if (!creature->creatureData()->hasItem(transfer->requireItemId())) {
            log("Error: there is no required item for this transfer.");
            return;
        }
        
        creature->creatureData()->removeItemWithId(transfer->requireItemId());
    }
    
    _chapterRecord->setMoney(_chapterRecord->getMoney() - GameFormula::getDefaultTransferFee());
    
    // Update the Creature Data
    creature->definitionId = transfer->toCreatureDefId();
    creature->creatureData()->level = 1;
    creature->creatureData()->ap += FDRandom::valueFromRange(transfer->apRange());
    creature->creatureData()->dp += FDRandom::valueFromRange(transfer->dpRange());
    creature->creatureData()->dx += FDRandom::valueFromRange(transfer->dxRange());
    creature->creatureData()->hpMax += FDRandom::valueFromRange(transfer->hpRange());
    creature->creatureData()->mpMax += FDRandom::valueFromRange(transfer->mpRange());
    creature->creatureData()->mv += FDRandom::valueFromRange(transfer->mvRange());
    creature->creatureData()->hpCurrent = creature->creatureData()->hpMax;
    creature->creatureData()->mpCurrent = creature->creatureData()->mpMax;
    
    _layer->updateMoneyBar();
}
