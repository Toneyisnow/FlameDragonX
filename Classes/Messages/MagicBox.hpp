//
//  MagicBox.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef MagicBox_hpp
#define MagicBox_hpp

#include "cocos2d.h"
#include "Creature.hpp"
#include "MessageBox.hpp"

typedef enum MagicOperatingType
{
    MagicOperatingType_Select,
    MagicOperatingType_ShowOnly
} MagicOperatingType;

class MagicBox : public Message
{
private:
    
    Creature * _creature;
    MagicOperatingType _operatingType;
    
public:
    
    MagicBox(Creature * creature, MagicOperatingType type);
    
    
};

#endif /* MagicBox_hpp */
