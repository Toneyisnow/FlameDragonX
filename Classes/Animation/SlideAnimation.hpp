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
#include "Constants.hpp"

USING_NS_CC;

class SlideAnimation : public cocos2d::Ref
{
protected:
    
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
    void appendFrame(Texture2D * texture);
    
    virtual int getFrameCount();
    FDFrame * frameAt(int index);
    
    virtual FDFrame * frameAtTick(int tick);
    
    bool isRepeatable();
    bool isSynchronized();
    virtual int getTotalTick();
    
};

#endif /* SlideAnimation_hpp */
