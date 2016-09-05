//
//  TransparencyFrame.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#ifndef TransparencyFrame_hpp
#define TransparencyFrame_hpp

#include "cocos2d.h"
#include "FDFrame.hpp"

USING_NS_CC;

class TransparencyFrame : public FDFrame
{
private:
    
    float _opacity;
    
public:
    
    static TransparencyFrame * create(float opacity);
    
    TransparencyFrame(float opacity);
    ~TransparencyFrame();
    
    void renderFrame(Sprite * sprite);
    
};

#endif /* TransparencyFrame_hpp */
