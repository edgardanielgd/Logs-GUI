#ifndef BASE_DECODER_H
#define BASE_DECODER_H

#include <iostream>
#include <ctime>

using namespace std;

class BaseDecoder{
    public:
        string folderPath;    

        BaseDecoder( string _folderPath);
        ~BaseDecoder();
};
#endif