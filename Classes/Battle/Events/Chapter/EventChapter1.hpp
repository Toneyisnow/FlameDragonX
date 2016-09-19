//
//  EventChapter1.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventChapter1_hpp
#define EventChapter1_hpp


#include "cocos2d.h"
#include "EventChapterCommon.cpp"

class EventChapter1 : public EventChapterCommon
{
private:
    
public:
    
    void loadEvents() override;
    
    void round1();
    void round1_1();
    void round1_2();
    void round1_3();
    
    void round3();
    void round4();
    void round5_Boss();
    void round6_Npc();
    
};
#endif /* EventChapter1_hpp */
