//
//  Ground.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/24/16.
//
//

#include "Ground.hpp"


Ground * Ground::createGround(GroundType type)
{
    Ground * ground;
    switch (type) {
        case GroundTypeGround:
            ground = new Ground(type, 5, 0);
            break;
        case GroundTypeChasm:
            ground = new Ground(type, 0, 0);
            break;
        case GroundTypeMarsh:
            ground = new Ground(type, -5, -5);
            break;
        case GroundTypeGap:
            ground = new Ground(type, 0, 0);
            break;
        case GroundTypeBlackForest:
            ground = new Ground(type, -5, -5);
            break;
        case GroundTypeForest:
            ground = new Ground(type, -5, 10);
            break;
            
        default:
            break;
    }
    
    ground->autorelease();
    return ground;
}

Ground::Ground(GroundType type, int aPoint, int dPoint)
{
    this->_groundType = type;
    this->_attackPoint = aPoint;
    this->_defensePoint = dPoint;
}

int Ground::getAttackPoint()
{
    return _attackPoint;
}

int Ground::getDefensePoint()
{
    return _defensePoint;
}