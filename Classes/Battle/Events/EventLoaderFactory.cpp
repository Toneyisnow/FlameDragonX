//
//  EventLoaderFactory.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#include "EventLoaderFactory.hpp"
#include "EventChapter1.hpp"

EventLoader * EventLoaderFactory::getEventLoader(int chapterId)
{
    EventLoader * loader;
    
    switch (chapterId) {
        case 1:
            loader = new EventChapter1();
            break;
            
        default:
            break;
    }
    
    loader->autorelease();
    
    return loader;
}