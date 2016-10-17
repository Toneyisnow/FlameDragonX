//
//  CombinedActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#ifndef CombinedActivity_hpp
#define CombinedActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

USING_NS_CC;

class CombinedActivity : public FDActivity
{
protected:
    
    Vector<FDActivity *> _activityList;
    int _currentActivityIndex;
    
public:
    
    CombinedActivity();
    ~CombinedActivity();
    
    void appendActivity(FDActivity *activity);
    
    virtual void initialize() override;
    virtual void internalTick(int synchronizedTick) override;
    
    virtual int getTotalTick() override;
    virtual void reset() override;
    
    FDActivity * getCurrentActivity();
    int getCurrentIndex();
    
    
};
#endif /* CombinedActivity_hpp */
