//
//  CreatureChapterRecord.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef CreatureChapterRecord_hpp
#define CreatureChapterRecord_hpp

#include <stdio.h>
#include "cocos2d.h"

class CreatureBattleRecord;

USING_NS_CC;

class CreatureChapterRecord : public cocos2d::Ref
{
private:
    
    int creatureId;
    int definitionId;
    int creatureType;
    
    ////  CreatureData *data;
    Point location;
    
public:
    
    
    static CreatureChapterRecord * createByBattleRecord(CreatureBattleRecord * record);
    
    
};

#endif /* CreatureChapterRecord_hpp */
