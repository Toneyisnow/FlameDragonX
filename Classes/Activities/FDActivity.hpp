//
//  FDActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef FDActivity_hpp
#define FDActivity_hpp

#include "cocos2d.h"

class BattleScene;
class BattleField;

USING_NS_CC;

class FDActivity : public cocos2d::Ref
{
protected:
    
    // BattleScene * _battle;
    // BattleField * _field;
    
    
    bool _isInitialized;
    bool _hasFinished;
    
    
public:
    
    FDActivity();
    // FDActivity(BattleScene * battle);
    
    virtual void initialize();
    virtual void internalTick(int synchronizedTick);
    void takeTick(int synchronizedTick);
    
    bool hasFinished();
    
    
};

#endif /* FDActivity_hpp */
