//
//  TouchHandler.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef TouchHandler_hpp
#define TouchHandler_hpp

#include "cocos2d.h"
USING_NS_CC;

class BattleField;


class TouchHandler : public cocos2d::Ref
{
private:
    
    const int MOVE_MARGIN_SIZE = 50;
    
    BattleField * _field;
    Point _deltaPoint;
    
    bool _hasTouchMoved;
    
public:
    
    TouchHandler(BattleField * field);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
    void moveFieldTo(Vec2 position);
    
    
};
#endif /* TouchHandler_hpp */
