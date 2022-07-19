#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <cstddef>

template <typename K, typename V>
class LinkedList
{
    public:

        LinkedList(){};
        ~LinkedList();

        bool isEmpty();
        bool add( K key, V *value, bool updateOnExistence = false);
        bool update( K key, V *newValue);
        V* find( K key );

        struct LinkedListNode {
            K key;
            V *value;
            LinkedListNode *next;
        };

        LinkedListNode *first = NULL;

};

#endif