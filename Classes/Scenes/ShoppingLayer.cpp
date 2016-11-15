//
//  ShoppingLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#include "ShoppingLayer.hpp"
#include "Constants.hpp"
#include "ShoppingAmorDialog.hpp"
#include "ShoppingItemDialog.hpp"
#include "ShoppingSecretDialog.hpp"
#include "ShoppingBarDialog.hpp"
#include "ShoppingChurchDialog.hpp"

ShoppingLayer::ShoppingLayer(ChapterRecord * chapterRecord, ShopType type)
{
    _chapterRecord = chapterRecord;
    _chapterRecord->retain();
    _shopType = type;
    
    std::string filename = StringUtils::format("Village/VillageShop-01-%d.png", _shopType);
    ScaledSprite * mainSprite = ScaledSprite::create(filename);
    Size screen = Constants::getScreenSize();
    mainSprite->setPosition(screen.width / 2, screen.height / 2);
    mainSprite->setScale(Constants::DEFAULT_SPRITE_SCALE);
    
    this->addChild(mainSprite);
    
    switch (_shopType) {
        case ShopType_Amor:
            _homeDialog = new ShoppingAmorDialog();
            break;
        case ShopType_Item:
            _homeDialog = new ShoppingItemDialog();
            break;
        case ShopType_Secret:
            _homeDialog = new ShoppingSecretDialog();
            break;
        case ShopType_Bar:
            _homeDialog = new ShoppingBarDialog();
            break;
        case ShopType_Church:
            _homeDialog = new ShoppingChurchDialog();
            break;
            
        default:
            break;
    }
    
    _homeDialog->showDialog(this);
    _activeDialog = nullptr;
    _activeMessage = nullptr;
    
    //Adding Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(ShoppingLayer::onClicked, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

void ShoppingLayer::setActiveDialog(ShoppingDialog * dialog)
{
    if (_activeDialog != nullptr) {
        _activeDialog->autorelease();
        _activeDialog = nullptr;
    }
    
    if (dialog != nullptr) {
        _activeDialog = dialog;
        _activeDialog->retain();
    }
}

void ShoppingLayer::setActiveMessage(Message * message)
{
    if (_activeMessage != nullptr)
    {
        _activeMessage->autorelease();
        _activeMessage = nullptr;
    }
    
    if (message != nullptr)
    {
        _activeMessage = message;
        _activeMessage->retain();
    }
}

ChapterRecord * ShoppingLayer::getRecord()
{
    return _chapterRecord;
}

bool ShoppingLayer::onClicked(Touch* touch, Event* event)
{
    log("Clicked on ShoppingLayer.");
    
    if (_activeMessage != nullptr) {
        _activeMessage->handleClick(touch->getLocation());
        return true;
    }
    
    Size screenSize = Constants::getScreenSize();
    if (touch->getLocation().y > screenSize.height / 2)
    {
        if (_activeDialog != nullptr) {
            _activeDialog->closeDialog();
        }
        else
        {
            //Exit
            auto f = [](Scene* scene) {
                return TransitionFade::create(1.0f, scene);
            };
            Director::getInstance()->popScene(f);
        }
    }
    
    return true;
}

void ShoppingLayer::updateMoneyBar()
{
    
}
