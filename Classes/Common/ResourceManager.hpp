//
//  ResourceManager.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/22/16.
//
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class ResourceManager : public cocos2d::Ref
{
public:
    
    static Sprite* loadSprite();
    
};


#endif /* ResourceManager_hpp */
