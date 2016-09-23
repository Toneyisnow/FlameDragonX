//
//  LevelUpDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef LevelUpDefinition_hpp
#define LevelUpDefinition_hpp

#include "cocos2d.h"
#include "FDRange.hpp"
#include "TextFileReader.hpp"

class LevelUpDefinition : public cocos2d::Ref
{
private:
    
    int _definitionId;
    
    FDRange * _hpRange;
    FDRange * _mpRange;
    FDRange * _apRange;
    FDRange * _dpRange;
    FDRange * _dxRange;
    
    
public:
  
    static LevelUpDefinition * readFromFile(TextFileReader *reader);
    LevelUpDefinition(TextFileReader * reader);
    
    int definitionId();
    FDRange * hpRange();
    FDRange * mpRange();
    FDRange * apRange();
    FDRange * dpRange();
    FDRange * dxRange();
    
    
};

#endif /* LevelUpDefinition_hpp */
