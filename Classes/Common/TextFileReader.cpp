//
//  TxtFileReader.cpp
//  PixelPoem
//
//  Created by SuiYi on 6/7/16.
//
//

#include "TextFileReader.hpp"
#include "FDRange.hpp"

using namespace std;

TextFileReader::TextFileReader(std::string relativePath)
{
    inputStream.open( FileUtils::getInstance()->fullPathForFilename(relativePath.c_str()).c_str());
    
}

TextFileReader::~TextFileReader()
{
    inputStream.close();
    
}

int TextFileReader::readInt()
{
    string content = readString();
    return atoi(content.c_str());
}

string TextFileReader::readString()
{
    char content[256];
    inputStream >> content;
    
    return content;
}

FDRange * TextFileReader::readRange()
{
    int min = this->readInt();
    int max = this->readInt();
    
    return FDRange::rangeWithValues(min, max);
}