#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>

#define MAX_NODES 10  // Maximum number of nodes in the graph

typedef struct Edge {
    int target;          // Target node index
    int weight;         // Weight (travel time)
    struct Edge* next;   // Pointer to the next edge in the list
} Edge;

typedef struct Node {
    char* name;         // Name of the node (junction/sector)
    Edge* edges;        // List of edges
} Node;

typedef struct Graph {
    Node nodes[MAX_NODES]; // Array of nodes
    int nodeCount;         // Current number of nodes
} Graph;

// Function prototypes
void initializeGraph(Graph* graph);
int addNode(Graph* graph, const char* name);
void addEdge(Graph* graph, const char* from, const char* to, int weight);
void dijkstra(Graph* graph, const char* startNode, const char* endNode);
void freeGraph(Graph* graph);

#endif // GRAPH_H
