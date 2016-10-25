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
#include "CreatureData.hpp"

USING_NS_CC;

class CreatureRecord : public cocos2d::Ref
{
private:
    
    
    CreatureData * _data;
    
    /// Point location;
    
public:
    
    //// static CreatureBattleRecord * createByChapterRecord(CreatureChapterRecord * record);
    
    int creatureId;
    int definitionId;
    int creatureType;
    
};

#endif /* CreatureRecord_hpp */
