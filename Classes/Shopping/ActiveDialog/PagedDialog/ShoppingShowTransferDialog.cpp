//
//  ShoppingShowTransferDialog.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/4/16.
//
//

#include "ShoppingShowTransferDialog.hpp"
#include "DataStore.hpp"
#include "LocalizedStrings.hpp"
#include "TouchableLabel.hpp"
#include "TouchableSprite.hpp"

using namespace std;

ShoppingShowTransferDialog::ShoppingShowTransferDialog(Vector<CreatureRecord *> &creatures, int pageIndex)
: ShoppingPagedDialog(pageIndex)
{
    _transferList.clear();
    
    for (CreatureRecord * creature : creatures) {
        
        if (creature->creatureData()->level < 20) {
            continue;
        }
        
        TransfersDefinition * transfers = DataStore::getInstance()->getTransfersDefinition(creature->definitionId);
        
        if (transfers == nullptr || transfers->totalCount() == 0) {
            continue;
        }
        
        for (int i = 0; i < transfers->totalCount(); i++) {
            TransferDefinition * transfer = transfers->getTransfer(i);
            if (transfer->requireItemId() == 0 || creature->creatureData()->hasItem(transfer->requireItemId()))
            {
                _transferList.pushBack(transfer);
            }
        }
    }
}


void ShoppingShowTransferDialog::showDialog(ShoppingLayer * layer)
{
    ShoppingPagedDialog::showDialog(layer);
    
    int startX = 15;
    int startY = 58;
    int intervalY = 26;
    
    int startIndex = _pageIndex * this->getMaxPerPage();
    
    for (int i = 0; i + startIndex < this->getTotalCount() && i < this->getMaxPerPage(); i++) {
        int index = i + startIndex;
        
        TransferDefinition * transfer = _transferList.at(index);
        CreatureDefinition * fromCreatureDef = DataStore::getInstance()->getCreatureDefinition(transfer->fromCreatureDefId());
        CreatureDefinition * toCreatureDef = DataStore::getInstance()->getCreatureDefinition(transfer->toCreatureDefId());
        
        std::string fromOccupation = fromCreatureDef->getOccupationName();
        std::string toOccupation = toCreatureDef->getOccupationName();
        
        std::string message = StringUtils::format(LocalizedStrings::getInstance()->getMessageString(70).c_str(), fromOccupation.c_str(), toOccupation.c_str());
        
        TouchableSprite * iconSprite = TouchableSprite::create(StringUtils::format("Icons/%03d/Icon-%03d-02.png", transfer->fromCreatureDefId(), transfer->fromCreatureDefId()));
        iconSprite->setTag(transfer->transferId());
        iconSprite->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowTransferDialog::onClicked));
        iconSprite->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addChild(iconSprite, Vec2(startX, startY - intervalY * i));
        
        TouchableLabel * messageLabel = TouchableLabel::createWithTTF(message, "fonts/mini_black.ttf", 14);
        messageLabel->setTag(transfer->transferId());
        messageLabel->setCallback(this, CALLBACK1_SELECTOR(ShoppingShowTransferDialog::onClicked));
        messageLabel->setAnchorPoint(Vec2(0, 0));
        _baseSprite->addLabel(messageLabel, Vec2(startX + 25, startY - intervalY * i));
    }
}

int ShoppingShowTransferDialog::getMaxPerPage()
{
    return 3;
}

int ShoppingShowTransferDialog::getTotalCount()
{
    return (int)_transferList.size();
}

void ShoppingShowTransferDialog::onClicked(int transferId)
{
    
}
