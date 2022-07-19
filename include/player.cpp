#include <player.h>

bool operator< (const IP& current, const IP& comparedTo ){
    for(int i = 0; i < 4; i++){
        const int block_ic = current.blocks[i];
        const int block_io = comparedTo.blocks[i];

        if( block_ic > block_io ) return false;
        if( block_ic < block_io) return true;
    }
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