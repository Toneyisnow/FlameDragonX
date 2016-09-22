//
//  ScaledSprite.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef ScaledSprite_hpp
#define ScaledSprite_hpp

#include "cocos2d.h"

USING_NS_CC;

class ScaledSprite : public cocos2d::Sprite
{
    
private:
    
    
public:
    
    static ScaledSprite* create(const std::string& filename);

    void setScaledPosition(Vec2 position);
    
    void setScale(float scale) override;
    
    void addChild(Node * child, Vec2 position);
    void addLabel(Label * label, Vec2 position);
    
};

#endif /* ScaledSprite_hpp */
