//
//  GroundActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#ifndef GroundActivity_hpp
#define GroundActivity_hpp

#include "cocos2d.h"
#include "FDActivity.hpp"

class BattleField;

USING_NS_CC;

class FieldActivity : public FDActivity
{
protected:
    
    BattleField * _battleField;
    
    
public:
    
    FieldActivity(BattleField * field);
    
    
};


#endif /* GroundActivity_hpp */
