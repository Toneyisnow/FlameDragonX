//
//  ShoppingLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingLayer_hpp
#define ShoppingLayer_hpp

#include "cocos2d.h"
#include "ChapterRecord.hpp"
#include "ShopDefinition.hpp"
#include "ShoppingHomeDialog.hpp"

USING_NS_CC;

class ShoppingLayer : public Layer
{
private:
    
    ShopType _shopType;
    ShoppingHomeDialog * _homeDialog;
    ShoppingDialog * _activeDialog;
    
    ChapterRecord * _chapterRecord;
    
    bool onClicked(Touch* touch, Event* event);
    
public:
    
    ShoppingLayer(ChapterRecord * chapterRecord, ShopType type);
    
    ChapterRecord * getRecord();
    
    void setActiveDialog(ShoppingDialog * dialog);
};

#endif /* ShoppingLayer_hpp */
