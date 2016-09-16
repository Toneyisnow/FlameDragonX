//
//  DatoBar.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef DatoBar_hpp
#define DatoBar_hpp

#include "cocos2d.h"

USING_NS_CC;

class DatoBar : public cocos2d::Ref
{
private:
    
    Sprite * _baseSprite;
    
public:
    
    DatoBar(int creatureAniId);
    
    Sprite * getSprite();
    
};


#endif /* DatoBar_hpp */
