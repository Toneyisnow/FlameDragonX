//
//  MovePathResolver.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/19/16.
//
//

#ifndef MovePathResolver_hpp
#define MovePathResolver_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "FDPoint.hpp"
#include "RoutePoint.hpp"
#include "PointMap.hpp"

class BattleField;

class MovePathPoint : public cocos2d::Ref
{
    
public:
    
    static MovePathPoint * create(Vec2 pos, MovePathPoint * previousPoint, int moved, int h);
    
    Vec2 position;
    MovePathPoint * previousPoint;
    
    int movedPoint;
    int heuristicPoint;
    int totalPoint;
    
};

class MovePathResolver : public cocos2d::Ref
{
private:
    
    BattleField * _battleField;
    Creature * _creature;
    Vec2 _targetPosition;
    RoutePoint * _resultRoute;
    PointMap<Creature *> * _zocPositions;
    
    bool _hasReachedTarget;
    
    void enqueue(Vector<MovePathPoint *> &positionQueue, MovePathPoint * point);
    
public:
    
    MovePathResolver(BattleField * field, Creature * creature, Vec2 targetPosition);
    ~MovePathResolver();
    
    void calculate();
    
    RoutePoint * getRoutePoint();
};

#endif /* MovePathResolver_hpp */
