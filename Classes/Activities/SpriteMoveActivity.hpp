//
//  SpriteMoveActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/16/16.
//
//

#ifndef SpriteMoveActivity_hpp
#define SpriteMoveActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

USING_NS_CC;

class SpriteMoveActivity : public FDActivity
{
private:
    
    Sprite * _object;
    Vec2 _targetLocation;
    
    float _duration;
    
public:
    
    SpriteMoveActivity(Sprite * object, Vec2 toPosition, float duration);
    ~SpriteMoveActivity();
    
    void initialize();
    void internalTick(int synchronizeTick);
    
};
#endif /* SpriteMoveActivity_hpp */
