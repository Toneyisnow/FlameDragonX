//
//  MoveScopeResolver.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#include "MoveScopeResolver.hpp"
#include "ResolverHelper.hpp"


MoveScopePoint * MoveScopePoint::create(Vec2 pos, int p)
{
    MoveScopePoint * point = new MoveScopePoint();
    point->position = pos;
    point->movePoint = p;
    
    point->autorelease();
    return point;
}

MoveScopeResolver::MoveScopeResolver(BattleField * field, Creature * creature)
{
    this->_field = field;
    this->_creature = creature;
    this->_originPosition = field->getObjectPosition(creature);
    
    _zocPositions = new PointMap<Creature *>();
    _movePoints = new Vector<MoveScopePoint *>();
    _scopeResults = new PointMap<FDPoint *>();
}

MoveScopeResolver::~MoveScopeResolver()
{
    
    _movePoints->clear();
    delete _movePoints;
    
    _scopeResults->release();
}


void MoveScopeResolver::calculate()
{
    // Resolve the ZOC Positions
    _zocPositions = ResolverHelper::calculateZocPositions(_field, _creature);
    _zocPositions->retain();
    
    Vector<Creature *> * enemyList = _field->getEnemyList();
    for (int i = 0; i < enemyList->size(); i++) {
        Creature * enemy = enemyList->at(i);
        
        int distance = _field->getObjectDistance(_creature, enemy);
        if (distance <= _creature->creatureData()->mv)
        {
            Vec2 enemyPosition = _field->getObjectPosition(enemy);
            
            _zocPositions->insert(Vec2(enemyPosition.x + 1, enemyPosition.y), enemy);
            _zocPositions->insert(Vec2(enemyPosition.x - 1, enemyPosition.y), enemy);
            _zocPositions->insert(Vec2(enemyPosition.x, enemyPosition.y + 1), enemy);
            _zocPositions->insert(Vec2(enemyPosition.x, enemyPosition.y - 1), enemy);
        }
    }
    
    // Start Point
    Vec2 startPoint = _field->getObjectPosition(_creature);
    _movePoints->pushBack(MoveScopePoint::create(startPoint, _creature->creatureData()->mv));
    _scopeResults->insert(startPoint, FDPoint::create(startPoint));
    
    while (_movePoints->size() > 0) {
        
        MoveScopePoint * currentPoint = _movePoints->at(0);
        _movePoints->erase(0);
        
        log("Walk Point: (%d, %d)", (int)currentPoint->position.x, (int)currentPoint->position.y);
        walkDirection(currentPoint, -1, 0);
        walkDirection(currentPoint, +1, 0);
        walkDirection(currentPoint, 0, -1);
        walkDirection(currentPoint, 0, +1);
    }
    
    // Remove the positions that contains Creature
    std::vector<Vec2> keys = _scopeResults->keys();
    for (int i = 0; i < keys.size(); i++) {
        Vec2 point = keys.at(i);
        Creature * creatureAtPos = _field->getCreatureAt(point.x, point.y);
        if (creatureAtPos != nullptr && creatureAtPos != _creature)
        {
            _scopeResults->eraseObject(point);
        }
    }
    
    _zocPositions->release();
}

void MoveScopeResolver::walkDirection(MoveScopePoint * lastPoint, int directionX, int directionY)
{
    Vec2 lastPosition = lastPoint->position;
    int moveLeft = lastPoint->movePoint;
    
    Vec2 currentPos = lastPosition;
    while (moveLeft > 0)
    {
        currentPos.x = currentPos.x + directionX;
        currentPos.y = currentPos.y + directionY;
        
        // Calculate according to map and creature
        int moveCount = ResolverHelper::calculateMovePoint(_field, _creature, currentPos);
        if (moveCount < 0)
        {
            return;
        }
        
        moveLeft -= moveCount;
        if (moveLeft < 0)
        {
            return;
        }
        
        // If it is Enemy
        Creature * c = _field->getCreatureAt(currentPos.x, currentPos.y);
        if (c != nullptr && c->getType() == CreatureType_Enemy) {
            return;
        }
        
        // ZOC
        if (_zocPositions->containsKey(currentPos))
        {
            moveLeft = 0;
        }
        
        // Add valid position to the result
        if (!_scopeResults->containsKey(currentPos))
        {
            log("Adding Point: (%d, %d)", (int)currentPos.x, (int)currentPos.y);
            _scopeResults->insert(currentPos, FDPoint::create(lastPosition));
        
            if (moveLeft > 0)
            {
                _movePoints->pushBack(MoveScopePoint::create(currentPos, moveLeft));
            }
        }
    }
}

Vector<FDPoint *> MoveScopeResolver::getResults()
{
    Vector<FDPoint *> results;
    
    std::vector<Vec2> keys = _scopeResults->keys();
    for (int i = 0; i < keys.size(); i++) {
        Vec2 point = keys.at(i);
        results.pushBack(FDPoint::create(point));
    }
    
    return results;
}

RoutePoint * MoveScopeResolver::getRoutePoint(Vec2 point)
{
    RoutePoint * route = new RoutePoint();
    
    route->insertPoint(point);
    
    FDPoint * nextPoint = _scopeResults->at(point);
    while (nextPoint != nullptr && nextPoint->getValue() != _originPosition)
    {
        Vec2 position = nextPoint->getValue();
        route->insertPoint(position);
        nextPoint = _scopeResults->at(position);
    }
    
    route->autorelease();
    return route;
}
