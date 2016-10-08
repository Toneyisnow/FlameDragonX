//
//  GameOverLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/7/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp


#include "cocos2d.h"
#include "FDScreen.hpp"

class GameOverLayer : public cocos2d::Layer
{
private:
    
    void closeScene(float dt);

public:
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverLayer);
    
};
#endif /* GameOverLayer_hpp */
