//
//  LocalizedStrings.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/15/16.
//
//

#include "LocalizedStrings.hpp"

USING_NS_CC;

LocalizedStrings * LocalizedStrings::_instance = nullptr;

LocalizedStrings * LocalizedStrings::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new LocalizedStrings();
    }
    
    return _instance;
}

LocalizedStrings::LocalizedStrings()
{
    
}

LocalizedStrings::~LocalizedStrings()
{
    
}

void LocalizedStrings::loadBasicStrings()
{
    Dictionary *language = Dictionary::createWithContentsOfFile("ch.plist");

    _creatureNames = Dictionary::createWithContentsOfFile("Strings/zh-cn/Creature.strings");
}


void LocalizedStrings::loadChapterStrings(int chapterId)
{
    
}

std::string LocalizedStrings::getCreatureName(int creatureId)
{
    std::string key = StringUtils::format("%03d", creatureId);
    String* str = (String*)_creatureNames->objectForKey(key.c_str());
    std::string result(str->getCString());
    
    return result;
}