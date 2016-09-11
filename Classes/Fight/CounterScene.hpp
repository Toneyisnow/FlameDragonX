//
//  FightScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef CounterScene_hpp
#define CounterScene_hpp

#include "cocos2d.h"
#include "CounterInfo.hpp"

class CounterScene : public cocos2d::Scene
{
protected:
    
    CounterInfo * _information;
    
    Layer * _layer;
    
public:
    
    CounterScene(CounterInfo * info);
    ~CounterScene();
};

#endif /* FightScene_hpp */
