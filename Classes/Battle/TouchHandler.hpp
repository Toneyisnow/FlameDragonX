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
    
    int _totalTouchCount;
    
    BattleField * _field;
    Point _deltaPoint;
    float _benchMarkScale;
    float _originScale;
    float _originDistance;
    
    Touch * _firstTouch;
    Touch * _secondTouch;
    
    bool _hasTouchMoved;
    
public:
    
    TouchHandler(BattleField * field);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
    bool onTouchesBegan(const std::vector<Touch*>& touches, Event* evt);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* evt);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* evt);
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event* evt);
    
    void moveFieldTo(Vec2 position);
    
    void test();
    
};
#endif /* TouchHandler_hpp */
