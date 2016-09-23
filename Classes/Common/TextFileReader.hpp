
//
//  TxtFileReader.hpp
//  PixelPoem
//
//  Created by SuiYi on 6/7/16.
//
//

#ifndef TextFileReader_hpp
#define TextFileReader_hpp

#include <stdio.h>
#include <fstream>
#include "cocos2d.h"
#include "FDRange.hpp"

USING_NS_CC;
using namespace std;

class TextFileReader : public Ref
{
private:
    
    ifstream inputStream;
public:
    
    
    TextFileReader(std::string relativePath);
    ~TextFileReader();
    
    int readInt();
    std::string readString();
    FDRange * readRange();
    
};



#endif /* TextFileReader_hpp */
