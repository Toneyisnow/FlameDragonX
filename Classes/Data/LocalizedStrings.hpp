//
//  LocalizedStrings.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#ifndef LocalizedStrings_hpp
#define LocalizedStrings_hpp

#include "cocos2d.h"

USING_NS_CC;

class LocalizedStrings : public Ref
{
private:
    
    static LocalizedStrings * _instance;

    Dictionary * _creatureNames;
    Dictionary * _itemNames;
    Dictionary * _magicNames;
    Dictionary * _messages;
    Dictionary * _occupations;
    Dictionary * _races;
    Dictionary * _villageShops;
    
    Dictionary * _chapterStrings;
    
public:
    
    LocalizedStrings();
    ~LocalizedStrings();
    
    static LocalizedStrings * getInstance();
    
    void loadBasicStrings();
    void loadChapterStrings(int chapterId);
    
    std::string getCreatureName(int creatureId);
    
};

#endif /* LocalizedStrings_hpp */
