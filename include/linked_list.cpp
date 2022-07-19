#include "linked_list.h"
#include <cstddef>

template <typename K, typename V>
bool LinkedList<K,V>::isEmpty(){
    return (first == NULL);
}

template <typename K, typename V>
bool LinkedList<K,V>::add( K key, V* value, bool updateOnExistence){
    
    if( key == NULL || value == NULL ){
        return false;
    }

    LinkedListNode *newNode = new LinkedListNode;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    LinkedListNode *temp = first;
    LinkedListNode *temp2 = NULL;

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
        
    temp2->next = newNode;
    newNode->next = temp;

    return true;
}

template <typename K, typename V>
V *LinkedList<K,V>::find( K key){
    
    if( isEmpty() ) return NULL;

    LinkedListNode *temp = first;

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

    LinkedListNode *temp = first;

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

    LinkedListNode *temp = first;
    LinkedListNode *temp2 = NULL;

    while( temp != NULL ){

        delete temp->value;

        temp2 = temp->next;
        delete temp;
        temp = NULL;
        temp = temp2;
    }
}