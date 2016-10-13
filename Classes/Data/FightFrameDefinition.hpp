//
//  FightFrameDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/10/16.
//
//

#ifndef FightFrameDefinition_hpp
#define FightFrameDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"

class FightFrameDefinition : public cocos2d::Ref
{
private:
    
    int _interval;
    int _soundId;
    bool _isRemote;
    float _hittingRate;
    
public:
    
    //// static FightFrameDefinition * readFromFile(TextFileReader * reader, std::string filename);
    FightFrameDefinition(int interval, int soundId, bool isRemote, float hittingRate);
    
    int interval();
    int soundId();
    bool isRemote();
    float hittingRate();
    bool isHitting();
    
};

#endif /* FightFrameDefinition_hpp */
