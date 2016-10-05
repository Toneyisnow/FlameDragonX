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
#include "ScaledSprite.hpp"

USING_NS_CC;

class DatoBar : public cocos2d::Ref
{
private:
    
    ScaledSprite * _baseSprite;
    
public:
    
    DatoBar(int creatureAniId);
    
    ScaledSprite * getSprite();
    
};


#endif /* DatoBar_hpp */
