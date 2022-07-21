#include "linked_list.h"
#include "player.h"
#include "default_decoder.h"

#include <iostream>
#include <filesystem>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

DefaultDecoder::DefaultDecoder( string _folderPath ) : BaseDecoder(_folderPath) {
    for( const auto& entry : filesystem::directory_iterator(_folderPath) ){
        
        file *newFile = new file;
        filesystem::path fPath = entry.path();

        if( fPath.has_filename() ){
            newFile->path = fPath.filename().generic_string();

            cout << newFile->path << endl;
            regex re("\\[(\\d{2})-(\\d{2})-(\\d{4})\\]\\.FullLog\\.txt");
            smatch match;

            bool matches = regex_search(folderPath, match, re);
            matches = matches && match.size() == 4;

            if( matches ){
                int day = atoi( match.str( 1 ).c_str() );
                int month = atoi( match.str( 2 ).c_str() );
                int year = atoi( match.str( 3 ).c_str() );

                tm* timeinfo = new tm;

                timeinfo->tm_mday = day;
                timeinfo->tm_mon = month;
                timeinfo->tm_year = year;

                CustomTime ct;
                ct.time = mktime( timeinfo );

                newFile->date = ct;

                files.add( ct, newFile );
            }
        }
        
    }
}

void DefaultDecoder::readAndInsert(){

}

DefaultDecoder::~DefaultDecoder(){}
