//
//  StringUtil.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef StringUtil_hpp
#define StringUtil_hpp

#include "cocos2d.h"
USING_NS_CC;

class StringUtil : public Ref
{
public:
    
    template <typename... Ts>
    static std::string format (const std::string &fmt, Ts... vs)
    {
        char b;
        unsigned required = std::snprintf(&b, 0, fmt.c_str(), vs...) + 1;
        // See comments: the +1 is necessary, while the first parameter
        //               can also be set to nullptr
        
        char bytes[required];
        std::snprintf(bytes, required, fmt.c_str(), vs...);
        
        return std::string(bytes);
    }
};
#endif /* StringUtil_hpp */
