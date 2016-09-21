//
//  ShowMessageActivity.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#ifndef ShowMessageActivity_hpp
#define ShowMessageActivity_hpp

#include "cocos2d.h"
#include "Message.hpp"
#include "GlobalActivity.hpp"

class BattleScene;

class ShowMessageActivity : public GlobalActivity
{
private:
    
    Message * _message;
    
public:
    
    static ShowMessageActivity * create(BattleScene * scene, Message * message);
    ShowMessageActivity(BattleScene * scene, Message * message);
    
    void initialize();
    void internalTick(int synchronizedTick);
};


#endif /* ShowMessageActivity_hpp */
