//
//  TeamEliminatedCondition.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "TeamEliminatedCondition.hpp"


#include "BattleScene.hpp"
#include "BattleField.hpp"

TeamEliminatedCondition::TeamEliminatedCondition(CreatureType teamType)
{
    _type = EventTypeTriggered;
    
    _teamType = teamType;
}

bool TeamEliminatedCondition::isMatch(BattleScene * scene)
{
    Vector<Creature *> list;
    switch (_teamType) {
        case CreatureType_Friend:
            list = *(scene->getBattleField()->getFriendList());
            break;
        case CreatureType_Enemy:
            list = *(scene->getBattleField()->getEnemyList());
            break;
        case CreatureType_Npc:
            list = *(scene->getBattleField()->getNPCList());
            break;
            
        default:
            break;
    }
    
    return (list.size() == 0);
}
