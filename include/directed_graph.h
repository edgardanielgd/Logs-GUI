#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "linked_list.h"
#include <cstddef>

template <typename K, typename KN, typename KV, typename V>
/*
    K <- general graph key
    KN <- individual nodes key (targets linked list)
    KV <- values linked list key (for each node)
    V <- Type of value (Player)   
*/
class DirectedGraph {
    public:

        DirectedGraph(){};
        ~DirectedGraph();

        bool isEmpty();
        bool add( K key, KV key2, V* value );
        LinkedList<KV,V>* find( K key );
        V* find( K key, KV key2 );
        bool update( K key, KV key2, V* value);

        struct DirectedGraphNode {
            LinkedList<KN,DirectedGraphNode> *directedTargets;
            LinkedList<KV,V> *values;
        };

        DirectedGraphNode *rootTargets = NULL;
    
    private:
        void deleteNodeData( DirectedGraphNode *d);
};
#endif