//
//  TransferDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef TransferDefinition_hpp
#define TransferDefinition_hpp

#include "cocos2d.h"
#include "FDRange.hpp"
#include "TextFileReader.hpp"

class TransferDefinition : public cocos2d::Ref
{
private:
    
    int _transferId;
    int _fromCreatureDefId;
    int _toCreatureDefId;
    int _requireItemId;
    
    FDRange * _hpRange;
    FDRange * _mpRange;
    FDRange * _apRange;
    FDRange * _dpRange;
    FDRange * _dxRange;
    FDRange * _mvRange;
    
    
public:
    
    static TransferDefinition * readFromFile(int fromCreatureId, TextFileReader *reader);
    TransferDefinition(int fromCreatureId, TextFileReader * reader);
    
    int transferId();
    int fromCreatureDefId();
    int toCreatureDefId();
    int requireItemId();
    
    FDRange * hpRange();
    FDRange * mpRange();
    FDRange * apRange();
    FDRange * dpRange();
    FDRange * dxRange();
    FDRange * mvRange();
    
    
};

#endif /* TransferDefinition_hpp */
