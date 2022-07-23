#ifndef DEFAULT_DECODER_H
#define DEFAULT_DECODER_H

#include "base_decoder.h"
#include "linked_list.h"
#include "player.h"

#include <iostream>
#include <ctime>

using namespace std;

class DefaultDecoder : BaseDecoder {
    public:

        DefaultDecoder( string _folderPath);
        ~DefaultDecoder();

        void readAndInsert(
            DirectedGraph<string,char,IP,Player> *& graphByName,
            DirectedGraph<IP,int,string,Player> *& graphByIp
        );

        struct file{
            string path;
            CustomTime date;
        };
        LinkedList<CustomTime,file> files;

        
};
#endif