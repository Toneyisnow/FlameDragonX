//
//  LoadingLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef LoadingLayer_hpp
#define LoadingLayer_hpp

#include "cocos2d.h"

USING_NS_CC;

class LoadingLayer : public Layer
{
private:
    
    bool onClicked(Touch* touch, Event* event);
    
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingLayer);

};

#endif /* LoadingLayer_hpp */
