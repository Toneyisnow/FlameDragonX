//
//  SystemMenuState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "SystemMenuState.hpp"
#include "BattleField.hpp"
#include "BattleScene.hpp"
#include "IdleState.hpp"
#include "MenuCursor.hpp"
#include "RecordMenuState.hpp"
#include "SettingsMenuState.hpp"
#include "LocalizedStrings.hpp"
#include "ConfirmMessage.hpp"
#include "ShowMessageActivity.hpp"

SystemMenuState * SystemMenuState::create(BattleScene * scene, StateSession * session)
{
    SystemMenuState * state = new SystemMenuState();
    
    state->initWithSession(scene, session);
    
    state->autorelease();
    
    return state;
}

void SystemMenuState::onEnterState()
{
    // Show System Menu
    log("Show system menu");
    _battleField->showSystemMenuAt(3, _session->menuPosition);
}

void SystemMenuState::onExitState()
{
    log("Close system menu");
    _battleField->closeMenu();
}

void SystemMenuState::handleClickAt(Vec2 position)
{
    MenuCursor * menuItem = (MenuCursor *)_battleField->getObjectByPosition(BattleObject_Menu, position);
    
    if (menuItem == nullptr)
    {
        _nextState = IdleState::create(_battleScene);
        return;
    }
    
    if (!menuItem->isSelected())
    {
        if (menuItem->isValid())
        {
            _battleField->setActiveMenuCursor(menuItem);
        }
    }
    else
    {
        switch (menuItem->getId()) {
            case 30:
                // Matching
                return;
                break;
            case 31:
                // Record
                _nextState = RecordMenuState::create(_battleScene, _session);
                return;
            case 32:
                // Settings
                _nextState = SettingsMenuState::create(_battleScene, _session);
                return;
            case 33:
                // End Turn
                promptEndTurn();
                return;
            default:
                break;
        }
    }
}

void SystemMenuState::promptEndTurn()
{
    ConfirmMessage * confirm = new ConfirmMessage(LocalizedStrings::getInstance()->getConfirmString(1));
    confirm->setReturnFunction(this, CALLBACK1_SELECTOR(SystemMenuState::confirmEndTurn));
    ShowMessageActivity * activity = ShowMessageActivity::create(_battleScene, confirm);
    _battleScene->getActivityQueue()->appendActivity(activity);
    confirm->autorelease();
}

void SystemMenuState::confirmEndTurn(int confirmed)
{
    log("Confirm result: %d", confirmed);
    
    _battleScene->waiveAllTurn();
    
    _nextState = IdleState::create(_battleScene);
    _battleField->notifyStateDispatcher();
}

