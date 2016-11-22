//
//  AIMagicDefensiveDelegate.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/23/16.
//
//

#include "AIMagicDefensiveDelegate.hpp"
#include "BattleScene.hpp"
#include "CreatureMoveActivity.hpp"

AIMagicDefensiveDelegate::AIMagicDefensiveDelegate(AICreature * creature, BattleScene * scene)
: AIActiveDelegate(creature, scene)
{
    
}

void AIMagicDefensiveDelegate::takeAction()
{
    log("AIMagicDefensiveDelegate for creature %d", _creature->getId());
    
    if (!_creature->isPendingAction())
    {
        this->takeMagicAction();
    }
    else
    {
        this->takePendingAction();
    }
}

void AIMagicDefensiveDelegate::takeMagicAction()
{
    Vector<MagicDefinition *> availableMagicList = this->getAvailableMagicList();
    if (availableMagicList.size() == 0) {
        _foundAvailableMagic = false;
        _creature->pendingAction();
        return;
    }
    _foundAvailableMagic = true;
    
    Map<MagicDefinition *, Creature *> candidateMagicList = this->getCandidateMagicList(availableMagicList);
    if (candidateMagicList.size() == 0) {
        _foundAvailableTarget = false;
        _creature->pendingAction();
        return;
    }
    _foundAvailableTarget = true;
    
    MagicDefinition * magic = this->chooseMagicFromCandidate(candidateMagicList.keys());
    Vec2 position = this->findOptimizedMagicPosition(magic, candidateMagicList.at(magic));
    
    // Use the magic
    _battleScene->magicTo(_creature, magic->getDefinitionId(), position);
    
}

void AIMagicDefensiveDelegate::takePendingAction()
{
    Creature * nearestFriend = this->locateNearestFriend();
    
    if (nearestFriend != nullptr) {
        
        // Move to the nearest friend
        MoveScopeResolver * scopeResolver = new MoveScopeResolver(_battleField, _creature);
        scopeResolver->calculate();
        
        Vec2 friendPosition = _battleField->getObjectPosition(nearestFriend);
        Vec2 decidedPosition = this->findReachMovePosition(scopeResolver, friendPosition);
        
        this->setCreatureMoved(decidedPosition);
        RoutePoint * route = scopeResolver->getRoutePoint(decidedPosition);
        CreatureMoveActivity * activity = CreatureMoveActivity::create(_battleField, _creature, route);
        _battleScene->getActivityQueue()->appendActivity(activity);
        scopeResolver->release();
    }
    else
    {
        // Cannot find any friend, just stand by
        _battleScene->waiveTurn(_creature);
    }
}
