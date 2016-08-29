//
//  SlideAnimation.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/25/16.
//
//

#ifndef SlideAnimation_hpp
#define SlideAnimation_hpp

#include "cocos2d.h"
#include "FDFrame.hpp"

// USING_NS_CC;

typedef enum Direction
{
    DirectionUp = 0,
    DirectionDown = 1,
    DirectionLeft = 2,
    DirectionRight = 3
} Direction;


class SlideAnimation : public cocos2d::Ref
{
private:
    
    int _defaultFrameTickCount;
    bool _isRepeatable;
    bool _isSynchronized;
    int _totalTick;
    
    Vector<FDFrame *> _frameList;
    
public:
    
    SlideAnimation(int defaultFrameTickCount, bool isRepeatable, bool isSynchronized);
    ~SlideAnimation();
    
    void appendFrame(FDFrame * frame);
    void appendFrame(std::string filename);
    
    int getFrameCount();
    FDFrame * frameAt(int index);
    
    FDFrame * frameAtTick(int tick);
    
    bool isRepeatable();
    bool isSynchronized();
    int getTotalTick();
    
};

#endif /* SlideAnimation_hpp */
