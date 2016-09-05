//
//  SpriteFrame.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef FDFrame_hpp
#define FDFrame_hpp

#include "cocos2d.h"

USING_NS_CC;

class FDFrame : public cocos2d::Ref
{
protected:
    
    Texture2D * _texture;
    int _tickCount;
    
    Texture2D * getTexture();
    
public:
    
    FDFrame();
    FDFrame(std::string filename);
    FDFrame(std::string filename, int tickCount);
    ~FDFrame();
    
    void setTickCount(int count);
    int getTickCount();
    
    virtual void renderFrame(Sprite * sprite);
    
    
};

#endif /* SpriteFrame_hpp */
