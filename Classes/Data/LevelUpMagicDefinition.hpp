//
//  LevelUpMagicDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef LevelUpMagicDefinition_hpp
#define LevelUpMagicDefinition_hpp

#include "cocos2d.h"
#include "FDRange.hpp"
#include "TextFileReader.hpp"

class LevelUpMagicDefinition : public cocos2d::Ref
{
private:
    
    int _definitionId;
    int _creatureLevel;
    int _magicId;
    
public:
    
    static LevelUpMagicDefinition * readFromFile(TextFileReader *reader);
    LevelUpMagicDefinition(int defId, TextFileReader * reader);
    
    int definitionId();
    int creatureLevel();
    int magicId();
    
   
};

#endif /* LevelUpMagicDefinition_hpp */
