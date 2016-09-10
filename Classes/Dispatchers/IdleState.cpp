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

ActionState * IdleState::handleClickAt(Vec2 position)
{
    Creature * creature = _battleField->getCreatureAt(position.x, position.y);
    
    if (creature != nullptr)
    {
        _battleField->setCursorTo(position);
        
        if (creature->getType() == CreatureType_Friend && !creature->hasTakenAction() && !creature->isFrozen())
        {
            _session->creaturePositionBeforeMove = position;
            _session->setSelectedCreatureId(creature->getId());
            return ShowMoveScopeState::create(_battleScene, _session);
        }
        else if (creature->isVisible())
        {
            // Show information about the creature
            
            return nullptr;
        }
    }
    else
    {
        // Show system menu
        if (CommonHelper::IsSamePosition(_battleField->getCursorPosition(), position))
        {
            _session->menuPosition = position;
            return SystemMenuState::create(_battleScene, _session);
        }
        
        _battleField->setCursorTo(position);
    }
    
    return nullptr;
}