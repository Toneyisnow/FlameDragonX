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
    _chapterStrings = nullptr;
}

LocalizedStrings::~LocalizedStrings()
{
    
}

void LocalizedStrings::loadBasicStrings()
{
    Dictionary *language = Dictionary::createWithContentsOfFile("ch.plist");

    _creatureNames = Dictionary::createWithContentsOfFile("Strings/zh-cn/Creature.strings");
    _creatureNames->retain();
}


void LocalizedStrings::loadChapterStrings(int chapterId)
{
    if (_chapterStrings != nullptr)
    {
        _chapterStrings->release();
    }
    
    std::string filename = StringUtils::format("Strings/zh-cn/Maps/Chapter-%02d.strings", chapterId);
    _chapterStrings = Dictionary::createWithContentsOfFile(filename.c_str());
    _chapterStrings->retain();
}

std::string LocalizedStrings::getCreatureName(int creatureId)
{
    std::string key = StringUtils::format("%03d", creatureId);
    String* str = (String*)_creatureNames->objectForKey(key.c_str());
    std::string result(str->getCString());
    
    return result;
}

int LocalizedStrings::getConversationCreatureId(int chapterId, int conversationId, int sequenceId)
{
    std::string key = StringUtils::format("%02d-%02d-%03d-Id", chapterId, conversationId, sequenceId);
    String* str = (String*)_chapterStrings->objectForKey(key.c_str());
    
    return atoi(str->getCString());
}

std::string LocalizedStrings::getConversation(int chapterId, int conversationId, int sequenceId)
{
    std::string key = StringUtils::format("%02d-%02d-%03d", chapterId, conversationId, sequenceId);
    String* str = (String*)_chapterStrings->objectForKey(key.c_str());
    std::string result(str->getCString());
    
    return result;
}