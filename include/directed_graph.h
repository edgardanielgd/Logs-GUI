#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "linked_list.h"
#include "player.h"

#include <cstddef>

template <typename KN, typename KV, typename V>
struct DirectedGraphNode {
    LinkedList<KN,DirectedGraphNode < KN, KV, V> > *directedTargets;
    LinkedList<KV,V> *values;
    KV lastKnownKey;
};

template <typename K, typename KN, typename KV, typename V>
/*
    K <- general graph key
    KN <- individual nodes key (targets linked list)
    KV <- values linked list key (for each node)
    V <- Type of value (Player)   
*/
class DirectedGraph {
    private:
        void deleteNodeData( DirectedGraphNode<KN,KV,V> *d){
            delete d->values;
            
            if( d->directedTargets != NULL ){

                LinkedListNode<KN, DirectedGraphNode<KN,KV,V>> *temp = d->directedTargets->first;

                while( temp != NULL ){
                    deleteNodeData( temp->value );
                    temp = temp->next;
                }

                delete d->directedTargets;
            }  
            
            delete d;    
        };

    public:

        DirectedGraph(){};
        ~DirectedGraph(){
            DirectedGraphNode<KN,KV,V> *temp = rootTargets;

            if( temp == NULL) return;
            deleteNodeData( temp );
        };

        bool isEmpty(){
            return (rootTargets == NULL);
        };

        DirectedGraphNode<KN,KV,V>* getNodeByKey( k key );
        bool add( K key, KV key2, V* value );
        LinkedList<KV,V>* find( K key );
        V* find( K key, KV key2 );
        bool update( K key, KV key2, V* value);

        DirectedGraphNode<KN,KV,V> *rootTargets = NULL;
    
};
#endif