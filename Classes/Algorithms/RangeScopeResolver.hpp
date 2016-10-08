//
//  RangeScopeResolver.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef RangeScopeResolver_hpp
#define RangeScopeResolver_hpp

#include "cocos2d.h"
#include "FDPoint.hpp"
#include "FDRange.hpp"

USING_NS_CC;

class BattleField;

class RangeScopeResolver : public cocos2d::Ref
{
private:
    
    BattleField * _field;
    Vec2 _point;
    FDRange * _range;
    
public:
    
    RangeScopeResolver(BattleField * field, Vec2 point, FDRange * range);
    
    Vector<FDPoint *> calculcate();
    
    void appendPoint(Vector<FDPoint *> &list, int x, int y);
};

#endif /* RangeScopeResolver_hpp */
