//
//  EventLoaderFactory.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/2/16.
//
//

#ifndef EventLoaderFactory_hpp
#define EventLoaderFactory_hpp


#include "cocos2d.h"
#include "EventLoader.hpp"

class EventLoaderFactory : public cocos2d::Ref
{
private:
    
public:
    
    static EventLoader * getEventLoader(int chapterId);
};

#endif /* EventLoaderFactory_hpp */
