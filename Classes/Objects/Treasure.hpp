//
//  Treasure.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/20/16.
//
//

#ifndef Treasure_hpp
#define Treasure_hpp

#include "cocos2d.h"

#include "BattleObject.hpp"

class Treasure : public BattleObject
{
private:
    
    int _itemId;
    int _boxType;
    
    bool _hasOpened;
    
public:
    
    Treasure(int itemId, int type);
    
    int itemId();
    int boxType();
    bool hasOpened();
    
    void setOpened(bool value);
    void changeItem(int itemId);
    
};

#endif /* Treasure_hpp */
