//
//  OffsetFrame.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/5/16.
//
//

#ifndef OffsetFrame_hpp
#define OffsetFrame_hpp

#include "cocos2d.h"
#include "FDFrame.hpp"

USING_NS_CC;

class OffsetFrame : public FDFrame
{
private:
    
    Vec2 _offset;
    
public:
    
    OffsetFrame(std::string filename, Vec2 offset);
    ~OffsetFrame();
    
    
};

#endif /* OffsetFrame_hpp */
