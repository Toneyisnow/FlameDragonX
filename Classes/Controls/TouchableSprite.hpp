//
//  TouchableSprite.hpp
//  FlameDragonX
//
//  Created by SuiYi on 11/3/16.
//
//

#ifndef TouchableSprite_hpp
#define TouchableSprite_hpp

#include "ScaledSprite.hpp"
#include "CallbackMethod.hpp"

class TouchableSprite : public ScaledSprite
{
private:
    
    Ref * _callbackObject;
    SEL_CALLBACK0 _callbackMethod0;
    SEL_CALLBACK1 _callbackMethod1;
    
    
public:
    
    static TouchableSprite* create(const std::string& filename);
    bool initWithFile(const std::string& filename) override;
    
    void setCallback(Ref * obj, SEL_CALLBACK0 callback);
    void setCallback(Ref * obj, SEL_CALLBACK1 callback);
    
    bool onSpriteTouchBegin(Touch* touch, Event* event);
    void onSpriteTouched(Touch* touch, Event* event);
};

#endif /* TouchableSprite_hpp */
