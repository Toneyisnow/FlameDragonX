//
//  MovePathResolver.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/19/16.
//
//

#include "MovePathResolver.hpp"
#include "BattleField.hpp"
#include "ResolverHelper.hpp"

MovePathPoint * MovePathPoint::create(Vec2 pos, MovePathPoint * previousPoint, int moved, float h)
{
    MovePathPoint * point = new MovePathPoint();
    
    point->position = pos;
    point->previousPoint = previousPoint;
    point->movedPoint = moved;
    point->heuristicPoint = h;
    point->totalPoint = moved + h;
    
    point->autorelease();
    return point;
}

MovePathResolver::MovePathResolver(BattleField * field, Creature * creature, Vec2 targetPosition)
{
    _battleField = field;
    _creature = creature;
    _targetPosition = targetPosition;
    _resultRoute = nullptr;
}

MovePathResolver::~MovePathResolver()
{
    if (_resultRoute != nullptr)
    {
        _resultRoute->release();
    }
}

void MovePathResolver::calculate()
{
    Vec2 creaturePosition = _battleField->getObjectPosition(_creature);
    int totalDistance = _battleField->getPositionDistance(creaturePosition, _targetPosition);
    _zocPositions = ResolverHelper::calculateZocPositions(_battleField, _creature);
    _visitedPositions = new PointMap<Ref *>();
    
    
    Vector<MovePathPoint *> positionQueue;
    MovePathPoint * originPoint = MovePathPoint::create(creaturePosition, nullptr, 0, totalDistance);
    positionQueue.pushBack(originPoint);
    _hasReachedTarget = false;
    int minHeuristic = totalDistance;
    MovePathPoint * resultPoint = originPoint;
    
    while (!positionQueue.empty()) {
        
        // Pop the point
        MovePathPoint * currentPoint = positionQueue.at(0);
        positionQueue.erase(0);
        
        if (currentPoint->heuristicPoint < minHeuristic) {
            minHeuristic = currentPoint->heuristicPoint;
            resultPoint = currentPoint;
        }
        
        if (currentPoint->position == _targetPosition) {
            _hasReachedTarget = true;
            break;
        }
        
        if (currentPoint->position != creaturePosition && _zocPositions->containsKey(currentPoint->position)) {
            continue;
        }
        
        // push 4 nodes of the node
        Vec2 position = currentPoint->position;
        Vec2 deltaPoints[] = { Vec2(0, 1), Vec2(1, 0), Vec2(0, -1), Vec2(-1, 0) };
        for (Vec2 deltaPoint : deltaPoints) {
            Vec2 candidatePosition = Vec2(position.x + deltaPoint.x, position.y + deltaPoint.y);
            
            if (_visitedPositions->containsKey(candidatePosition)) {
                continue;
            }
            
            int movePoint = ResolverHelper::calculateMovePoint(_battleField, _creature, candidatePosition);
            if (movePoint < 0) {
                continue;
            }
            
            int movedPoint = currentPoint->movedPoint + movePoint;
            float heuristicPoint = ResolverHelper::calculateHeuristicPoint(candidatePosition, _targetPosition);
            MovePathPoint * newPoint = MovePathPoint::create(candidatePosition, currentPoint, movedPoint, heuristicPoint);
            
            this->enqueue(positionQueue, newPoint);
        }
    }
    
    _visitedPositions->release();
    
    // Generate the Result
    _resultRoute = new RoutePoint();
    MovePathPoint * nextPoint = resultPoint;
    while (nextPoint->movedPoint > _creature->creatureData()->mv && nextPoint->previousPoint != nullptr) {
        nextPoint = nextPoint->previousPoint;
    }
    
    while (_battleField->getCreatureAt(nextPoint->position.x, nextPoint->position.y) != nullptr && nextPoint->previousPoint != nullptr){
        nextPoint = nextPoint->previousPoint;
    }
    
    while (nextPoint->previousPoint != nullptr) {
        _resultRoute->insertPoint(nextPoint->position);
        nextPoint = nextPoint->previousPoint;
    }
    
}

void MovePathResolver::enqueue(Vector<MovePathPoint *> &positionQueue, MovePathPoint * point)
{
    for (int i = 0; i < positionQueue.size(); i++) {
        if (point->totalPoint <= positionQueue.at(i)->totalPoint) {
            positionQueue.insert(i, point);
            return;
        }
    }
    
    positionQueue.pushBack(point);
    _visitedPositions->insert(point->position, this);
}


RoutePoint * MovePathResolver::getRoutePoint()
{
    return _resultRoute;
}
