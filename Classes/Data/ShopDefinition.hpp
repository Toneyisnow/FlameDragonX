//
//  ShopDefinition.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/22/16.
//
//

#ifndef ShopDefinition_hpp
#define ShopDefinition_hpp

#include "cocos2d.h"
#include "TextFileReader.hpp"
#include "FDNumber.hpp"

typedef enum ShopType
{
    ShopType_Amor = 1,
    ShopType_Item = 2,
    ShopType_Secret = 3,
    ShopType_Bar = 4,
    ShopType_Church = 5
} ShopType;

class ShopDefinition : public cocos2d::Ref
{
private:
    
    Vector<FDNumber *> _itemList;
    
public:
    
    static ShopDefinition * readFromFile(TextFileReader *reader);
    ShopDefinition(TextFileReader * reader);
    
    
    Vector<FDNumber *> itemList();
};



#endif /* ShopDefinition_hpp */
