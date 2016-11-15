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
#include "Message.hpp"

USING_NS_CC;

class ShoppingLayer : public Layer
{
private:
    
    ShopType _shopType;
    ShoppingHomeDialog * _homeDialog;
    ShoppingDialog * _activeDialog;
    Message * _activeMessage;
    Message * _oldActiveMessage;
    
    ChapterRecord * _chapterRecord;
    
    bool onClicked(Touch* touch, Event* event);
    
public:
    
    ShoppingLayer(ChapterRecord * chapterRecord, ShopType type);
    
    ChapterRecord * getRecord();
    
    void setActiveDialog(ShoppingDialog * dialog);
    void setActiveMessage(Message * message);
    
    void updateMoneyBar();
    
};

#endif /* ShoppingLayer_hpp */
