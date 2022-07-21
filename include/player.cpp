#include "player.h"
#include <iostream>

#include <bits/stdc++.h>

using namespace std;
//====== IP

IP::IP( string strIp ){
    regex re("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3}):(\\d{1,5})");
    smatch match;

    bool matches = regex_search(strIp,match,re);
    matches = matches && match.size() == 6;

    if( matches ){
        for(int i = 0; i < 4; i++){
            int block = atoi( match.str( i+1 ).c_str() );
            if( block >= 0 && block < 256 )
                blocks[i] = block;
        }
        int regport = atoi( match.str( 5 ).c_str() );

        if( regport > 0 && regport < 65536 )
            port = regport;
    }
    // Otherwise let all ip components at 0
}

IP::~IP(){}

bool operator< (const IP& current, const IP& comparedTo ){
    for(int i = 0; i < 4; i++){
        const int block_ic = current.blocks[i];
        const int block_io = comparedTo.blocks[i];

        if( block_ic > block_io ) return false;
        if( block_ic < block_io) return true;
    }
    return false;
}

bool operator> (const IP& current, const IP& comparedTo){
    return comparedTo < current;
}

bool operator<= (const IP& current, const IP& comparedTo){
    return !(current > comparedTo);
}

bool operator>= (const IP& current, const IP& comparedTo){
    return !(current < comparedTo);
}

bool operator== (const IP& current, const IP& comparedTo ){
    for(int i = 0; i < 4; i++){
        const int block_ic = current.blocks[i];
        const int block_io = comparedTo.blocks[i];

        if( block_ic != block_io ) return false;
    }
    return true;
}

bool operator!= (const IP& current, const IP& comparedTo){
    return !(current == comparedTo);
}

//====== MESSAGE

bool operator< (const Message& current, const Message& comparedTo ){
    return current.value < comparedTo.value;
}

bool operator> (const Message& current, const Message& comparedTo){
    return comparedTo < current;
}

bool operator<= (const Message& current, const Message& comparedTo){
    return !(current > comparedTo);
}

bool operator>= (const Message& current, const Message& comparedTo){
    return !(current < comparedTo);
}

bool operator== (const Message& current, const Message& comparedTo ){
    return current.value == comparedTo.value;
}

bool operator!= (const Message& current, const Message& comparedTo){
    return !(current == comparedTo);
}

//====== MESSAGE TIME

bool operator< (const CustomTime& current, const CustomTime& comparedTo ){
    time_t tim1 = current.time, tim2=comparedTo.time;

    double difference = difftime(tim1, tim2);

    return (difference < 0);
}

bool operator> (const CustomTime& current, const CustomTime& comparedTo){
    return comparedTo < current;
}

bool operator<= (const CustomTime& current, const CustomTime& comparedTo){
    return !(current > comparedTo);
}

bool operator>= (const CustomTime& current, const CustomTime& comparedTo){
    return !(current < comparedTo);
}

bool operator== (const CustomTime& current, const CustomTime& comparedTo ){
    time_t tim1 = current.time, tim2=comparedTo.time;

    double difference = difftime(tim1, tim2);

    return difference==0;
}

bool operator!= (const CustomTime& current, const CustomTime& comparedTo){
    return !( current == comparedTo );
}