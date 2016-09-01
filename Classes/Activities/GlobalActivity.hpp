//
//  GlobalActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#ifndef GlobalActivity_hpp
#define GlobalActivity_hpp

#include "cocos2d.h"
#include "FieldActivity.hpp"

class BattleScene;

USING_NS_CC;

class GlobalActivity : public FieldActivity
{
protected:
    
    BattleScene * _game;
    
    
public:
    
    GlobalActivity(BattleScene * game);
    
    
};

#endif /* GlobalActivity_hpp */
