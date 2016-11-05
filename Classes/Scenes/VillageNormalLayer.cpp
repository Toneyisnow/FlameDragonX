//
//  VillageNormalLayer.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/24/16.
//
//

#include "VillageNormalLayer.hpp"
#include "ScaledSprite.hpp"
#include "Constants.hpp"
#include "AnimationLibrary.hpp"
#include "ShopDefinition.hpp"
#include "LocalizedStrings.hpp"
#include "SceneCreator.hpp"


bool VillageNormalLayer::init()
{
    _tickCount = 0;
    return true;
}

VillageNormalLayer::~VillageNormalLayer()
{
    _cursorAnimate->release();
    
    if (_confirmExitMessage != nullptr) {
        _confirmExitMessage->release();
    }
    
    _villageLabel->release();
}

void VillageNormalLayer::loadWithRecord(ChapterRecord * record)
{
    VillageLayer::loadWithRecord(record);
    
    Size screen = Constants::getScreenSize();
    
    // Background
    std::string backgroundFile = StringUtils::format("Village/Village-%02d.png", getVillageImageId());
    ScaledSprite * backgroundImage = ScaledSprite::create(backgroundFile);
    backgroundImage->setPosition(screen.width / 2, screen.height / 2);
    backgroundImage->setScale(1.5f);
    this->addChild(backgroundImage);
    
    // Cursor
    _cursorPositionIndex = 1;
    _cursor = ScaledSprite::create("Icons/001/Icon-001-01.png");
    _cursor->setScale(1.5f);
    _cursor->setPosition(this->getCursorPosition(_cursorPositionIndex));
    this->addChild(_cursor);
    SlideAnimation * animation = AnimationLibrary::getInstance()->getIdleAnimation(1, false);
    _cursorAnimate = new FDAnimate(_cursor);
    _cursorAnimate->setAnimation(animation);
    
    // VillageLabel
    _villageLabel = new VillageLabel();
    _villageLabel->showDialog(this);
    _villageLabel->setPositionIndex(_cursorPositionIndex);
    
    _confirmExitMessage = nullptr;
    
    schedule(CC_SCHEDULE_SELECTOR(VillageNormalLayer::takeDeltaTimeTck), 1.0 / Constants::GAME_FPS);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(VillageNormalLayer::onClicked, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

void VillageNormalLayer::takeDeltaTimeTck(float dt)
{
    if (_cursorAnimate != nullptr) {
        _cursorAnimate->takeTick(_tickCount ++);
    }
}

bool VillageNormalLayer::onClicked(Touch* touch, Event* event)
{
    Vec2 position = touch->getLocation();
    
    if (_confirmExitMessage != nullptr)
    {
        _confirmExitMessage->handleClick(position);
    }
    else
    {
        for (int pos = 0; pos < 6; pos ++) {
            if (this->clickedOnPosition(position, this->getCursorPosition(pos))) {
                if (pos != _cursorPositionIndex) {
                    this->setCursorPositionIndex(pos);
                }
                else if (pos > 0)
                {
                    this->enterShop();
                }
                else
                {
                    this->promptExit();
                }
            }
        }
    }
    
    return true;
}

int VillageNormalLayer::getVillageImageId()
{
    int chapterId = _chapterRecord->getChapterId();
    switch (chapterId) {
        case 2:return 1;
        case 3:return 2;
        case 4:return 1;
        case 5:return 2;
        case 6:return 2;
        case 7:return 1;
        case 8:return 2;
        case 9:return 2;
        case 10:return 1;
        case 11:return 2;
        case 12:return 2;
        case 13:return 3;
        case 14:return 3;
        case 15:return 3;
        case 16:return 3;
        case 17:return 3;
        case 18:return 3;
        case 19:return 3;
        case 20:return 3;
        case 21:return 3;
        case 22:return 3;
        case 23:return 3;
        case 24:return 3;
        case 25:return 3;
        case 26:return 1;
        case 27:return 1;
        default: break;
    }
    
    return 1;
}

void VillageNormalLayer::enterShop()
{
    ShopType type;
    switch (_cursorPositionIndex) {
        case 1:
            type = ShopType_Item;
            break;
        case 2:
            type = ShopType_Church;
            break;
        case 3:
            type = ShopType_Bar;
            break;
        case 4:
            type = ShopType_Amor;
            break;
        case 5:
            type = ShopType_Secret;
            break;
        default:
            type = ShopType_Amor;
            break;
    }
    
    // Enter Shop Scene
    Scene * scene = SceneCreator::createShoppingScene(_chapterRecord, type);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void VillageNormalLayer::promptExit()
{
    _confirmExitMessage = new ConfirmMessage(LocalizedStrings::getInstance()->getConfirmString(1));
    _confirmExitMessage->setReturnFunction(this, CALLBACK1_SELECTOR(VillageNormalLayer::confirmExit));
    _confirmExitMessage->showDialog(this);
}

void VillageNormalLayer::confirmExit(int returnValue)
{
    if (returnValue == 0) {
        _confirmExitMessage->release();
        _confirmExitMessage = nullptr;
        return;
    }
    
    this->doExit();
}

bool VillageNormalLayer::clickedOnPosition(Vec2 clickedPos, Vec2 position)
{
    return (clickedPos.x > position.x - 20 && clickedPos.x < position.x + 20 &&
            clickedPos.y > position.y - 20 && clickedPos.y < position.y + 20 );
}

void VillageNormalLayer::setCursorPositionIndex(int positionIndex)
{
    _cursorPositionIndex = positionIndex;
    _cursor->setPosition(getCursorPosition(positionIndex));
    _villageLabel->setPositionIndex(positionIndex);
}

Vec2 VillageNormalLayer::getCursorPosition(int positionIndex)
{
    Size winSize = Constants::getScreenSize();
    
    switch (this->getVillageImageId()) {
        case 1:
            switch (positionIndex) {
                case 0:
                    return Vec2(winSize.width * 0.24, winSize.height * 0.10);
                case 1:
                    return Vec2(winSize.width * 0.52, winSize.height * 0.25);
                case 2:
                    return Vec2(winSize.width * 0.6, winSize.height * 0.58);
                case 3:
                    return Vec2(winSize.width * 0.15, winSize.height * 0.7);
                case 4:
                    return Vec2(winSize.width * 0.2, winSize.height * 0.4);
                case 5:
                    return Vec2(winSize.width * 0.08, winSize.height * 0.85);
                default:
                    return Vec2(0, 0);
            }
            break;
        case 2:
            switch (positionIndex) {
                case 0:
                    return Vec2(winSize.width * 0.24, winSize.height * 0.10);
                case 1:
                    return Vec2(winSize.width * 0.55, winSize.height * 0.25);
                case 2:
                    return Vec2(winSize.width * 0.8, winSize.height * 0.75);
                case 3:
                    return Vec2(winSize.width * 0.25, winSize.height * 0.77);
                case 4:
                    return Vec2(winSize.width * 0.2, winSize.height * 0.27);
                case 5:
                    return Vec2(winSize.width * 0.5, winSize.height * 0.85);
                default:
                    return Vec2(0, 0);
            }
        case 3:
            switch (positionIndex) {
                case 0:
                    return Vec2(winSize.width * 0.24, winSize.height * 0.10);
                case 1:
                    return Vec2(winSize.width * 0.52, winSize.height * 0.25);
                case 2:
                    return Vec2(winSize.width * 0.76, winSize.height * 0.55);
                case 3:
                    return Vec2(winSize.width * 0.35, winSize.height * 0.75);
                case 4:
                    return Vec2(winSize.width * 0.2, winSize.height * 0.4);
                case 5:
                    return Vec2(winSize.width * 0.68, winSize.height * 0.85);
                default:
                    return Vec2(0, 0);
            }
            break;
        default:
            break;
    }
    
    return Vec2(0, 0);
}
