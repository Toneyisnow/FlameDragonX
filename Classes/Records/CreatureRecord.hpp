//
//  CreatureRecord.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef CreatureRecord_hpp
#define CreatureRecord_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class CreatureRecord : public cocos2d::Ref
{
private:
    
    int creatureId;
    int definitionId;
    int creatureType;
    
    ////  CreatureData *data;
    Point location;
    
public:
    
    
};

#endif /* CreatureRecord_hpp */
