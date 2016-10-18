//
//  IdleState.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#include "IdleState.hpp"
#include "Creature.hpp"
#include "BattleField.hpp"
#include "BattleScene.hpp"
#include "ShowMoveScopeState.hpp"
#include "SystemMenuState.hpp"
#include "CommonHelper.hpp"
#include "CreatureInfoMessage.hpp"

IdleState * IdleState::create(BattleScene * scene)
{
    IdleState * idle = new IdleState();
    
    StateSession * session = StateSession::newSession();
    idle->initWithSession(scene, session);
    idle->autorelease();
    return idle;
}

void IdleState::onEnterState()
{
    
}
void IdleState::onExitState()
{
    
}

void IdleState::handleClickAt(Vec2 position)
{
    Creature * creature = _battleField->getCreatureAt(position.x, position.y);
    
    if (creature != nullptr)
    {
        _battleField->setCursorTo(position);
        
        if (creature->getType() == CreatureType_Friend && !creature->hasTakenAction() && !creature->isFrozen())
        {
            _session->creaturePositionBeforeMove = position;
            _session->setSelectedCreatureId(creature->getId());
            
            Vec2 location = _battleField->convertPositionToLocation(position);
            Vec2 screenLoc = _battleField->getScreenLocationByLocation(location);
            
            CreatureInfoMessage * bar = new CreatureInfoMessage(creature, screenLoc);
            _battleScene->showMessage(bar);
            bar->release();
            
            _nextState = ShowMoveScopeState::create(_battleScene, _session);
            return;
        }
        else if (creature->isVisible())
        {
            // Show information about the creature
            _battleScene->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::showItemStatus), creature);
            if (creature->knowMagic()) {
                _battleScene->appendMethodToActivity(CALLBACK2_SELECTOR(BattleScene::showMagicStatus), creature);
            }
            
            return;
        }
    }
    else
    {
        // Show system menu
        if (CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
        {
            _session->menuPosition = position;
            _nextState = SystemMenuState::create(_battleScene, _session);
        }
        
        _battleField->setCursorTo(position);
    }
    
}
