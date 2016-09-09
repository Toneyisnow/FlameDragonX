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
#include "FDPoint.hpp"

class MoveScopeResolver;

USING_NS_CC;

class StateSession : public cocos2d::Ref
{
private:
    int _selectedCreatureId;
    int _selectedItemIndex;
    int _selectedMagicIndex;
    
    MoveScopeResolver * _scopeResolver;
    
public:
    
    static StateSession * newSession();
    StateSession();
    ~StateSession();
    
    
    void setSelectedCreatureId(int val);
    void setSelectedItemIndex(int val);
    void setSelectedMagicIndex(int val);
    void setLastPosition(Vec2 position);
    void setMoveScopeResolver(MoveScopeResolver * _scopeResolver);
    
    int selectedCreatureId();
    int selectedItemIndex();
    int selectedMagicIndex();
    MoveScopeResolver * getMoveScopeResolver();
    
    Vec2 creaturePositionBeforeMove;
    Vec2 creaturePositionAfterMove;
    Vec2 menuPosition;
    
};

#endif /* StateSession_hpp */
