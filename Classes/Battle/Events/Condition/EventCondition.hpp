//
//  EventCondition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventCondition_hpp
#define EventCondition_hpp


#include "cocos2d.h"

class BattleScene;

class EventCondition : public cocos2d::Ref
{
private:
    
public:
    
    
    bool isMatch(BattleScene * scene);
    
};

#endif /* EventCondition_hpp */
