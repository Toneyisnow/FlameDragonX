//
//  StateSession.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/4/16.
//
//

#ifndef StateSession_hpp
#define StateSession_hpp

#include "cocos2d.h"

USING_NS_CC;

class StateSession : public cocos2d::Ref
{
private:
    int _selectedCreatureId;
    int _selectedItemIndex;
    int _selectedMagicIndex;
    
    Vec2 _lastPosition;
    
public:
    
    static StateSession * newSession();
    StateSession();
    
    
    void setSelectedCreatureId(int val);
    void setSelectedItemIndex(int val);
    void setSelectedMagicIndex(int val);
    void setLastPosition(Vec2 position);
    
    int selectedCreatureId();
    int selectedItemIndex();
    int selectedMagicIndex();
    Vec2 lastPosition();
    
};

#endif /* StateSession_hpp */
