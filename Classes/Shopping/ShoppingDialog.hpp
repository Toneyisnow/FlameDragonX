//
//  ShoppingDialog.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef ShoppingDialog_hpp
#define ShoppingDialog_hpp

#include "cocos2d.h"
#include "CallbackMethod.hpp"
#include "ChapterRecord.hpp"
#include "ScaledSprite.hpp"

class ShoppingLayer;

class ShoppingDialog : public cocos2d::Ref
{
protected:

    const Vec2 MESSAGE_POSITION = Vec2(10, 70);
    const int DEFAULT_FONT_SIZE = 14;
    
    ShoppingLayer * _layer;
    
    ScaledSprite * _baseSprite;
    ChapterRecord * _chapterRecord;
    
    Ref * _callbackNode;
    SEL_CALLBACK1 _callbackMethod;
    
    int _returnValue;
    
public:
    
    ShoppingDialog();
    // ShoppingDialog(ChapterRecord * record);
    
    virtual void showDialog(ShoppingLayer * layer);
    void closeDialog();
    
    void setCallback(Ref* node, SEL_CALLBACK1 method);
    
};

#endif /* ShoppingDialog_hpp */
