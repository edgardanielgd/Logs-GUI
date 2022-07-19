#ifndef PLAYER_H
#define PLAYER_H

#include "linked_list.h"
#include <iostream>
#include <ctime>

using namespace std;

class IP {
    // Custom comparable type
    public:
        unsigned char blocks[4]; // byte
        unsigned int port; // word

        IP();
        ~IP();

        friend bool operator< (const IP& current, const IP& comparedTo );

        friend bool operator> (const IP& current, const IP& comparedTo);

        friend bool operator<= (const IP& current, const IP& comparedTo);

        friend bool operator>= (const IP& current, const IP& comparedTo);

        friend bool operator== (const IP& current, const IP& comparedTo );
};

class Message{
    public:
        string value;
        time_t msg_time;

        Message();
        ~Message();

        friend bool operator< (const Message& current, const Message& comparedTo );

        friend bool operator> (const Message& current, const Message& comparedTo);

        friend bool operator<= (const Message& current, const Message& comparedTo);

        friend bool operator>= (const Message& current, const Message& comparedTo);

        friend bool operator== (const Message& current, const Message& comparedTo );
};

struct Player{
    string name;
    IP ip;
    LinkedList<string, Message> *messages;
    LinkedList<string, Message> *commands;
    double time_played;
};

#endif