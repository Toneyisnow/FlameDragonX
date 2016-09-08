//
//  MoveScopeResolver.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#include "MoveScopeResolver.hpp"

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
    _zocPositions->release();
    
    _movePoints->clear();
    delete _movePoints;
    
    _scopeResults->release();
}

int MoveScopeResolver::getDistance(Creature * c1, Creature * c2)
{
    Vec2 position1 = _field->getObjectPosition(c1);
    Vec2 position2 = _field->getObjectPosition(c2);
    
    return abs(position1.x - position2.x) + abs(position1.y - position2.y);
}

void MoveScopeResolver::calculate()
{
    // Resolve the ZOC Positions
    Vector<Creature *> * enemyList = _field->getEnemyList();
    for (int i = 0; i < enemyList->size(); i++) {
        Creature * enemy = enemyList->at(i);
        
        if (getDistance(_creature, enemy) <= _creature->creatureData()->mv)
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
        if (_field->getCreatureAt(point.x, point.y) != nullptr)
        {
            _scopeResults->eraseObject(point);
        }
    }
    
    
    
    
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
        
        if (currentPos.x <= 0 || currentPos.x > _field->getFieldSize().width
            || currentPos.y <= 0 || currentPos.y > _field->getFieldSize().height)
        {
            return;
        }
        
        // if is blocked on map
        if (false)
        {
            return;
        }
        
        // Calculate according to map and creature
        int moveCount = getMoveCount(currentPos);
        if (moveCount < 0)
        {
            return;
        }
        
        moveLeft -= moveCount;
        if (moveLeft < 0)
        {
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

int MoveScopeResolver::getMoveCount(Vec2 position)
{
    Ground * ground = _field->groundAt(position.x, position.y);
    if (ground == nullptr)
    {
        return -1;
    }
    
    CreatureDefinition * creatureDef = _creature->getDefinition();
    
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