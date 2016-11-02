//
//  TouchableLabel.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/1/16.
//
//

#ifndef TouchableLabel_hpp
#define TouchableLabel_hpp

#include "cocos2d.h"
#include "CallbackMethod.hpp"

USING_NS_CC;

/*
 
 Sample for using in the Layer:
 
 TouchableLabel * tLabel = TouchableLabel::createWithTTF("Hello", "fonts/Marker Felt.ttf", 8);
 tLabel->setTag(4);
 tLabel->setCallback(this, CALLBACK1_SELECTOR(TitleLayer::onLabelTouched));
 dialog->addChild(tLabel, Vec2(200, 30));
 
 
 */


class TouchableLabel : public Label
{
private:
    
    Node * _callbackObject;
    SEL_CALLBACK1 _callbackMethod;
    
public:
    
    static TouchableLabel * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
                                 const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                 TextVAlignment vAlignment = TextVAlignment::TOP);
    
    TouchableLabel(enum TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
          enum TextVAlignment vAlignment /* = TextVAlignment::TOP */);
    
    void setCallback(Node * obj, SEL_CALLBACK1 callback);
    
    bool onLabelTouchBegin(Touch* touch, Event* event);
    void onLabelTouched(Touch* touch, Event* event);
};

#endif /* TouchableLabel_hpp */
