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
private:
    
    Texture2D * _texture;
    Vec2 _offset;
    int _tickCount;
    
    Texture2D * getTexture();
    Vec2 getOffset();
    
public:
    
    FDFrame(std::string filename);
    FDFrame(std::string filename, int tickCount);
    FDFrame(std::string filename, Vec2 offset, int tickCount);
    ~FDFrame();
    
    void setTickCount(int count);
    
    void renderFrame(Sprite * sprite);
    int getTickCount();
    
    
};

#endif /* SpriteFrame_hpp */
