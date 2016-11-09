//
//  ChapterRecord.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef ChapterRecord_hpp
#define ChapterRecord_hpp

#include "cocos2d.h"
#include "CreatureRecord.hpp"

USING_NS_CC;

class ChapterRecord : public cocos2d::Ref
{
private:
    
    int _chapterId;
    int _money;
    
    Vector<CreatureRecord *> _friendRecordList;
    
public:
    
    ChapterRecord(int chapterId);
    
    static ChapterRecord * createSample();
    static CreatureRecord * createSampleCreatureRecord(int definitionId);
    
    static ChapterRecord * newGame();
    
    
    int getChapterId();
    
    void setMoney(int money);
    int getMoney();
    
    void addCreatureRecord(CreatureRecord * record);
    Vector<CreatureRecord *> &getFriendRecordList();
    
    CreatureRecord * getCreatureCarriesItem(int itemId);
    
};

#endif /* ChapterRecord_hpp */
