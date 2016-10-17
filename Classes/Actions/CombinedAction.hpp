//
//  CombinedAction.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/16/16.
//
//

#ifndef CombinedAction_hpp
#define CombinedAction_hpp

#include "cocos2d.h"
#include "FDAction.hpp"

class CombinedAction : public FDAction
{
private:
    
    Vector<FDAction *> _actionList;
    
    int _currentAction;
    
public:
    
    CombinedAction(Sprite * sprite);
    ~CombinedAction();
    
    void appendAction(FDAction * action);
    
    void takeTick(int synchronizedTick) override;
    
    bool hasFinished() override;
    
    int getTotalTick() override;
    
    void reset() override;
    
    FDAction * getCurrentAction();
    int getCurrentIndex();
    
};

#endif /* CombinedAction_hpp */
