#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>

template <typename K, typename V>
struct LinkedListNode {
    K key;
    V *value;
    LinkedListNode<K,V> *next;
    LinkedListNode() = default;
};

template <typename K, typename V>
class LinkedList
{
    public:

        LinkedList();
        ~LinkedList();

        bool isEmpty();
        bool add( K key, V *value, bool updateOnExistence = false);
        bool update( K key, V *newValue);
        V* find( K key );

        LinkedListNode<K,V> *first = NULL;

};

template <typename K, typename V>
LinkedList<K,V>::LinkedList(){}

template <typename K, typename V>
bool LinkedList<K,V>::isEmpty(){
    return (first == NULL);
}

template <typename K, typename V>
bool LinkedList<K,V>::add( K key, V* value, bool updateOnExistence){
    
    if( value == NULL ){
        return false;
    }

    LinkedListNode<K,V>* newNode = new LinkedListNode<K,V>;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    LinkedListNode<K,V> *temp = first;
    LinkedListNode<K,V> *temp2 = NULL;

    if( temp == NULL ){
        first = newNode;
        first->next = NULL;
        return true;
    }
        
    while( key > (temp->key)){
        temp2 = temp;
        temp = temp->next;

        if( temp == NULL)
            break;
    }

    if( temp != NULL && key == (temp->key) ){
        if( updateOnExistence ){
            temp->value = value;
            return true;
        }
        return false;
    }
        
    newNode->next = temp;
    temp2->next = newNode;
    return true;
}

template <typename K, typename V>
V *LinkedList<K,V>::find( K key){
    
    if( isEmpty() ) return NULL;

    LinkedListNode<K,V> *temp = first;

    while( key > (temp->key) ){
        temp = temp->next;

        if( temp == NULL){
            return NULL;
        }
    }

    if( key == (temp->key) ){
        return temp->value;
    }

    return NULL;
}

template <typename K, typename V>
bool LinkedList<K,V>::update( K key, V* newValue){
    
    if( isEmpty() ) return false;

    LinkedListNode<K,V> *temp = first;

    while( key > (temp->key) ){
        temp = temp->next;

        if( temp == NULL){
            return false;
        }
    }

    if( key == (temp->key) ){
        temp->value = newValue;
        return true;
    }

    return false;
}

template <typename K, typename V>
LinkedList<K,V>::~LinkedList(){

    LinkedListNode<K,V> *temp = first;
    LinkedListNode<K,V> *temp2 = NULL;

    while( temp != NULL ){

        delete temp->value;

        temp2 = temp->next;
        delete temp;
        temp = NULL;
        temp = temp2;
    }
}
#endif