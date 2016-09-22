//
//  Message.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#ifndef Message_hpp
#define Message_hpp

#include "cocos2d.h"
#include "CallbackMethod.hpp"
#include "FDActivity.hpp"

class MessageLayer;

class Message : public cocos2d::Ref
{
protected:
    
    const int DEFAULT_MESSAGEBOX_SCALE = 1.3f;
    
    int _returnValue;
    
    Ref* _callbackTarget;
    SEL_CALLBACK1 _callbackResultMethod;
    
    MessageLayer * _messageLayer;
    
    Sprite * _sprite;
    
    bool _isBlocking;
    
public:
    
    Message();
    
    void setReturnFunction(Ref * target, SEL_CALLBACK1 method);
    
    void showDialog(MessageLayer * layer);
    void closeDialog();
    
    virtual void initDialog();
    virtual void removeDialog();
    virtual FDActivity * onEnterActivity();
    virtual FDActivity * onExitActivity();
    
    virtual void handleClick(Vec2 location);
    
    bool isBlocking();
};

#endif /* Message_hpp */
