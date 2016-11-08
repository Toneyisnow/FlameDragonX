//
//  AttackItemDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/29/16.
//
//

#ifndef AttackItemDefinition_hpp
#define AttackItemDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FDRange.hpp"
#include "ItemDefinition.hpp"

USING_NS_CC;

class AttackItemDefinition : public ItemDefinition
{
private:
    
    // For Equip item
    int _itemCategory;	// For Attack Item: 1：剑 2：斧 3：矛 4：弓 5：爪 6：机械
    
    int _ap;
    int _hit;
    int _ev;
    int _dp;
    //int attackScope;
    FDRange * _attackRange;
    
    
public:
    
    static AttackItemDefinition * readFromFile(TextFileReader * reader);
    void initFromFile(TextFileReader * reader);
    
    ~AttackItemDefinition();
    
    int ap();
    int hit();
    int ev();
    int dp();
    FDRange * attackRange();
    
    int getPoisonRate();
    int itemCategory();
    
};

#endif /* AttackItemDefinition_hpp */
