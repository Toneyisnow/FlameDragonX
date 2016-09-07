//
//  ActivityQueue.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef ActivityQueue_hpp
#define ActivityQueue_hpp


#include "cocos2d.h"
#include "FDActivity.hpp"

USING_NS_CC;

class ActivityQueue : public cocos2d::Ref
{
private:
    
    Vector<FDActivity *> * _queuedActivityList;
    Vector<FDActivity *> * _singleActivityList;
    
    FDActivity * _currentActivity;
    
    int _appendToIndex;
    
public:
    
    ActivityQueue();
    ~ActivityQueue();
    
    void pushBackActivity(FDActivity * activity);
    void insertActivity(FDActivity * activity);
    
    void appendActivity(FDActivity * activity);
    void insertSingleActivity(FDActivity * activity);
    
    void takeTick(int synchronizedTick);
    
};


#endif /* ActivityQueue_hpp */
