//
//  CombinedAnimate.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/11/16.
//
//

#ifndef CombinedAnimate_hpp
#define CombinedAnimate_hpp

#include "cocos2d.h"
#include "FDAnimate.hpp"

class CombinedAnimate : public FDAnimate
{
private:
    
    Vector<FDAnimate *> _animateList;
    
public:
    
    CombinedAnimate(Sprite * sprite);
    ~CombinedAnimate();
    
    void appendAnimate(FDAnimate * animate);
    
    void takeTick(int synchronizedTick) override;
    
    bool hasFinished() override;
    
    int getTotalTick() override;
    
    FDAnimate * getCurrentAnimate();
    
};

#endif /* CombinedAnimate_hpp */
