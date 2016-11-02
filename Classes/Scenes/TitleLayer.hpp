//
//  TitleLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#ifndef TitleLayer_hpp
#define TitleLayer_hpp

#include <stdio.h>


#include "cocos2d.h"
#include "FDScreen.hpp"

class TitleLayer : public cocos2d::Layer
{
public:
    
    FDScreen * _screen;
    
    // implement the "static create()" method manually
    virtual bool init();
    CREATE_FUNC(TitleLayer);
    
    void onStartGame();
    void onLoadGame();
    void onContinueGame();
    
};




#endif /* TitleLayer_hpp */
