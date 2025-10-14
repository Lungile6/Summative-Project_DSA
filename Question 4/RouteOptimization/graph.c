#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

// Initialize the graph
void initializeGraph(Graph* graph) {
    graph->nodeCount = 0;
}

// Add a node to the graph
int addNode(Graph* graph, const char* name) {
    if (graph->nodeCount >= MAX_NODES) {
        return -1; // Maximum nodes reached
    }
    graph->nodes[graph->nodeCount].name = strdup(name);
    graph->nodes[graph->nodeCount].edges = NULL;
    graph->nodeCount++;
    return 0; // Success
}

// Add an edge to the graph
void addEdge(Graph* graph, const char* from, const char* to, int weight) {
    int fromIndex = -1, toIndex = -1;

    // Find indices for from and to nodes
    for (int i = 0; i < graph->nodeCount; i++) {
        if (strcmp(graph->nodes[i].name, from) == 0) {
            fromIndex = i;
        }
        if (strcmp(graph->nodes[i].name, to) == 0) {
            toIndex = i;
        }
    }

    if (fromIndex != -1 && toIndex != -1) {
        // Create a new edge for from
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        newEdge->target = toIndex;
        newEdge->weight = weight;
        newEdge->next = graph->nodes[fromIndex].edges;
        graph->nodes[fromIndex].edges = newEdge;

        // Create a new edge for to (bidirectional)
        newEdge = (Edge*)malloc(sizeof(Edge));
        newEdge->target = fromIndex;
        newEdge->weight = weight;
        newEdge->next = graph->nodes[toIndex].edges;
        graph->nodes[toIndex].edges = newEdge;
    } else {
        printf("Invalid node names.\n");
    }
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(Graph* graph, const char* startNode, const char* endNode) {
    int distances[MAX_NODES];
    int previous[MAX_NODES];
    int visited[MAX_NODES] = {0};
    int startIndex = -1, endIndex = -1;

    // Initialize distances and previous nodes
    for (int i = 0; i < graph->nodeCount; i++) {
        distances[i] = INT_MAX; // Set to infinity
        previous[i] = -1;       // No previous node
        if (strcmp(graph->nodes[i].name, startNode) == 0) {
            startIndex = i;     // Start node index
        }
        if (strcmp(graph->nodes[i].name, endNode) == 0) {
            endIndex = i;       // End node index
        }
    }

    if (startIndex == -1 || endIndex == -1) {
        printf("Invalid start or end node.\n");
        return;
    }

    distances[startIndex] = 0;

    for (int count = 0; count < graph->nodeCount - 1; count++) {
        // Find the minimum distance node
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < graph->nodeCount; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) break; // All reachable nodes visited

        visited[minIndex] = 1;

        // Update distances for adjacent nodes
        for (Edge* edge = graph->nodes[minIndex].edges; edge != NULL; edge = edge->next) {
            int target = edge->target;
            if (!visited[target] && distances[minIndex] + edge->weight < distances[target]) {
                distances[target] = distances[minIndex] + edge->weight;
                previous[target] = minIndex;
            }
        }
    }

    // Output the shortest path
    int totalDistance = distances[endIndex];
    if (totalDistance == INT_MAX) {
        printf("No path found from %s to %s.\n", startNode, endNode);
        return;
    }

    printf("Shortest path from %s to %s:\n", startNode, endNode);
    for (int at = endIndex; at != -1; at = previous[at]) {
        printf("%s ", graph->nodes[at].name);
    }
    printf("\nTotal travel time: %d\n", totalDistance);
}

// Free the graph's allocated memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->nodeCount; i++) {
        free(graph->nodes[i].name);
        Edge* edge = graph->nodes[i].edges;
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
}
