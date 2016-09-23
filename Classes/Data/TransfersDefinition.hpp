//
//  TransfersDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef TransfersDefinition_hpp
#define TransfersDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "TransferDefinition.hpp"

class TransfersDefinition : public cocos2d::Ref
{
private:
    
    int _creatureDefId;
    
    Vector<TransferDefinition *> _transferList;
    
public:
    
    static TransfersDefinition * readFromFile(TextFileReader *reader);
    TransfersDefinition(TextFileReader * reader);
    
    int creatureDefId();
    
    TransferDefinition * getTransfer(int index);
    int totalCount();
};

#endif /* TransfersDefinition_hpp */
