//
//  VillageLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/24/16.
//
//

#ifndef VillageLayer_hpp
#define VillageLayer_hpp

#include "cocos2d.h"
#include "ChapterRecord.hpp"

class VillageLayer : public cocos2d::Layer
{
protected:
    
    ChapterRecord * _chapterRecord;
    int _chapterId;
    
    bool needPickFriend();
    bool needAutoPickFriend();

public:
    
    virtual void loadWithRecord(ChapterRecord * record);
    
    void doExit();
};

#endif /* VillageLayer_hpp */
