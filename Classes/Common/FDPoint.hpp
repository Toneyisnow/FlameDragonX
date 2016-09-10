//
//  FDPoint.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#ifndef FDPoint_hpp
#define FDPoint_hpp

#include "cocos2d.h"
USING_NS_CC;

class FDPoint : public cocos2d::Ref
{
private:
    
    Vec2 _data;
    
public:
    
    static FDPoint * create(Vec2 point);
    static FDPoint * create(int x, int y);
    FDPoint(Vec2 point);
    
    Vec2 getValue();
    
    
};

#endif /* FDPoint_hpp */
