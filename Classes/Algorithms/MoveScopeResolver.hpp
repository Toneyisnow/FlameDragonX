//
//  MoveScopeResolver.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#ifndef MoveScopeResolver_hpp
#define MoveScopeResolver_hpp

#include "cocos2d.h"
#include "BattleField.hpp"
#include "Creature.hpp"
#include "RoutePoint.hpp"
#include "FDPoint.hpp"
#include "PointMap.hpp"

USING_NS_CC;

class MoveScopePoint : public cocos2d::Ref
{
    
public:
    
    static MoveScopePoint * create(Vec2 pos, int point);
    
    Vec2 position;
    int movePoint;
};

class MoveScopeResolver : public cocos2d::Ref
{
private:
    
    BattleField * _field;
    Creature * _creature;
    Vec2 _originPosition;
    
    PointMap<Creature *> * _zocPositions;
    //// Map<Vec2, Creature *> * _zocPositions;
    Vector<MoveScopePoint *> * _movePoints;
    //// Map<Vec2, FDPoint *> * _scopeResults;
    PointMap<FDPoint *> * _scopeResults;
    
    void walkDirection(MoveScopePoint * movePoint, int directionX, int directionY);
    //// int getMoveCount(Vec2 position);
    
public:
  
    MoveScopeResolver(BattleField * field, Creature * creature);
    ~MoveScopeResolver();
    
    void calculate();
    
    Vector<FDPoint *> getResults();
    
    RoutePoint * getRoutePoint(Vec2 point);
};

#endif /* MoveScopeResolver_hpp */
