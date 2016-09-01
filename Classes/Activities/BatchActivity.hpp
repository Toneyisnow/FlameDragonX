//
//  BatchActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#ifndef BatchActivity_hpp
#define BatchActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

USING_NS_CC;

class BatchActivity : public FDActivity
{
protected:
    
    Vector<FDActivity *> * _activityList;
    
public:
    
    BatchActivity();
    ~BatchActivity();
    
    void addActivity(FDActivity *activity);
    
    virtual void initialize();
    virtual void internalTick(int synchronizedTick);
    
    
};

#endif /* BatchActivity_hpp */
