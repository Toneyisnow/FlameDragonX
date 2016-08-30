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
#include "CreatureChapterRecord.hpp"

USING_NS_CC;

class ChapterRecord : public cocos2d::Ref
{
private:
    
    int _chapterId;
    int _money;
    
    Vector<CreatureChapterRecord> *_friendRecordList;
    
public:
    
    ChapterRecord(int chapterId);
    
    static ChapterRecord * createSample();
    
    
    
    int getChapterId();
};

#endif /* ChapterRecord_hpp */
