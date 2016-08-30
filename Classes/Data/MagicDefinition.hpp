//
//  MagicDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef MagicDefinition_hpp
#define MagicDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"

USING_NS_CC;

class MagicDefinition : public cocos2d::Ref
{
private:
    
public:
    
    MagicDefinition * readFromFile(TextFileReader * reader);
};

#endif /* MagicDefinition_hpp */
