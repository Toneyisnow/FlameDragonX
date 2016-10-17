//
//  FDAction.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#ifndef FDAction_hpp
#define FDAction_hpp

#include "cocos2d.h"

USING_NS_CC;

class FDAction : public cocos2d::Ref
{
protected:
    
    Sprite * _sprite;
    
    int _currentTick;
    bool _hasFinished;
    
    int _tag;
    
public:
    
    
    FDAction(Sprite * sprite);
    ~FDAction();
    
    virtual void reset();
    
    virtual void takeTick(int synchronizedTick);
    
    virtual bool hasFinished();
    
    void setTag(int tag);
    int getTag();
    
    virtual int getTotalTick();
};

#endif /* FDAction_hpp */
