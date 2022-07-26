#include "directed_graph.h"
#include "linked_list.h"
#include "player.h"
#include <cstddef>

#include <iostream>
using namespace std;

//===================================
// DEFINITION BY NAMES MAPPING
template <>
bool DirectedGraph<string,char,IP,Player>::getNodeByKey( string key, IP key2, Player *value ){
    const int length = key.length();

    DirectedGraphNode<char,IP,Player> *temp = rootTargets;

    if( temp == NULL ){
        temp = new DirectedGraphNode<char,IP,Player>;
        temp->directedTargets = new LinkedList<char,DirectedGraphNode<char,IP,Player>>();
        temp->values = new LinkedList<IP,Player>();
    }

    for( int i = 0; i < length; i++){
        char character = key.at(i);

        DirectedGraphNode<char,IP,Player> *nextNode = temp->directedTargets->find( character );

        if( nextNode == NULL ){
            nextNode = new DirectedGraphNode<char,IP,Player>;
            nextNode->directedTargets = new LinkedList<char,DirectedGraphNode<char,IP,Player>>();
            nextNode->values = new LinkedList<IP,Player>();

            temp->directedTargets->add( character, nextNode );
        }
        temp = nextNode;
    }

    return temp;
}

template <>
bool DirectedGraph<string,char,IP,Player>::add( string key, IP key2, Player *value ){

    DirectedGraphNode<char,IP,Player> *temp = getNodeByKey( key );

    temp->lastKnownKey = key2;

    return temp->values->add(key2, value, true);   
}

template <>
LinkedList<IP,Player>* DirectedGraph<string,char,IP,Player>::find( string key ){
    const int length = key.length();

    DirectedGraphNode<char,IP,Player> *temp = rootTargets;

    if( isEmpty() ) return NULL;

    for( int i = 0; i < length; i++){
        char character = key.at(i);

        DirectedGraphNode<char,IP,Player> *nextNode = temp->directedTargets->find( character );

        if( nextNode == NULL ) return NULL;
        temp = nextNode;
    }

    return temp->values;
    
}

template <>
Player* DirectedGraph<string,char,IP,Player>::find( string key, IP key2 ){
    LinkedList<IP,Player>* resultsByName = find(key);

    if( resultsByName == NULL ) return NULL;

    Player* result = resultsByName->find( key2 );

    return result;
}

template <>
bool DirectedGraph<string,char,IP,Player>::update( string key, IP key2, Player* value){
    LinkedList<IP,Player>* resultsByName = find(key);

    if( resultsByName == NULL ) return false;

    return resultsByName->update(key2,value);
}

//===================================
// DEFINITION BY IPS MAPPING (the one will be most used, since there are at most 4 levels in graph)

template <>
bool DirectedGraph<IP,int,string,Player>::getNodeByKey( IP key, string key2, Player *value ){
    const int length = sizeof(key.blocks)/sizeof(key.blocks[0]);

    DirectedGraphNode<int,string,Player> *temp = rootTargets;

    if( temp == NULL ){
        temp = new DirectedGraphNode<int,string,Player>;
        temp->directedTargets = new LinkedList<int,DirectedGraphNode<int,string,Player>>();
        temp->values = new LinkedList<string,Player>();
    }

    for( int i = 0; i < length; i++){
        int block = key.blocks[i];

        DirectedGraphNode<int,string,Player> *nextNode = temp->directedTargets->find( block );

        if( nextNode == NULL ){
            nextNode = new DirectedGraphNode<int,string,Player>;
            nextNode->directedTargets = new LinkedList<int,DirectedGraphNode<int,string,Player>>();
            nextNode->values = new LinkedList<string,Player>();

            temp->directedTargets->add( block, nextNode );
        }
        temp = nextNode;
    }

    return temp;
}

template <>
bool DirectedGraph<IP,int,string,Player>::add( IP key, string key2, Player *value ){
    
    DirectedGraphNode<int,string,Player> = getNodeByKey( key );

    temp->lastKnownKey = key2;

    return temp->values->add(key2, value, true);   
}

template <>
LinkedList<string,Player>* DirectedGraph<IP,int,string,Player>::find( IP key ){
    const int length = sizeof(key.blocks)/sizeof(key.blocks[0]);

    DirectedGraphNode<int,string,Player> *temp = rootTargets;

    if( isEmpty() ) return NULL;

    for( int i = 0; i < length; i++){
        int block = key.blocks[i];

        DirectedGraphNode<int,string,Player> *nextNode = temp->directedTargets->find( block );

        if( nextNode == NULL ) return NULL;
        temp = nextNode;
    }

    return temp->values;
    
}

template <>
Player* DirectedGraph<IP,int,string,Player>::find( IP key, string key2 ){
    LinkedList<string,Player>* resultsByName = find(key);

    if( resultsByName == NULL ) return NULL;

    Player* result = resultsByName->find( key2 );

    return result;
}

template <>
bool DirectedGraph<IP,int,string,Player>::update( IP key, string key2, Player* value){
    LinkedList<string,Player>* resultsByName = find(key);

    if( resultsByName == NULL ) return false;

    return resultsByName->update(key2,value);
}
