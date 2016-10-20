//
//  ResolverHelper.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/20/16.
//
//

#include "ResolverHelper.hpp"

int ResolverHelper::calculateMovePoint(BattleField * battleField, Creature * creature, Vec2 position)
{
    if (position.x <= 0 || position.x > battleField->getFieldSize().width
        || position.y <= 0 || position.y > battleField->getFieldSize().height)
    {
        return -1;
    }
    
    Ground * ground = battleField->groundAt(position.x, position.y);
    if (ground == nullptr)
    {
        return -1;
    }
    
    CreatureDefinition * creatureDef = creature->getDefinition();
    
    if (creatureDef->canFly())
    {
        switch (ground->getType()) {
            case GroundTypeGround:
            case GroundTypeChasm:
            case GroundTypeMarsh:
            case GroundTypeBlackForest:
            case GroundTypeForest:
                return 1;
            case GroundTypeGap:
                return -1;
            default:
                break;
        }
    }
    else
    {
        switch (ground->getType()) {
            case GroundTypeGround:
                return 1;
            case GroundTypeChasm:
            case GroundTypeGap:
                return -1;
            case GroundTypeMarsh:
                if (creatureDef->isKnight()) {
                    return 3;
                }
                else
                {
                    return 2;
                }
            case GroundTypeBlackForest:
            case GroundTypeForest:
                if (creatureDef->isKnight()) {
                    return 2;
                }
                else
                {
                    return 1;
                }
            default:
                break;
        }
    }
    
    return -1;
}

PointMap<Creature *> * ResolverHelper::calculateZocPositions(BattleField * battleField, Creature * creature)
{
    PointMap<Creature *> * zocPositions = new PointMap<Creature *>();
    Vector<Creature *> targets;
    
    if (creature->getType() == CreatureType_Enemy) {
        targets.pushBack(*(battleField->getFriendList()));
        targets.pushBack(*(battleField->getNPCList()));
    }
    else
    {
        targets.pushBack(*(battleField->getEnemyList()));
    }
    
    for (int i = 0; i < targets.size(); i++) {
        Creature * target = targets.at(i);
        
        int distance = battleField->getObjectDistance(creature, target);
        if (distance <= creature->creatureData()->mv)
        {
            Vec2 targetPosition = battleField->getObjectPosition(target);
            
            zocPositions->insert(Vec2(targetPosition.x + 1, targetPosition.y), target);
            zocPositions->insert(Vec2(targetPosition.x - 1, targetPosition.y), target);
            zocPositions->insert(Vec2(targetPosition.x, targetPosition.y + 1), target);
            zocPositions->insert(Vec2(targetPosition.x, targetPosition.y - 1), target);
        }
    }
    
    zocPositions->autorelease();
    
    return zocPositions;
}
