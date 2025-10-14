#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    Graph graph;
    initializeGraph(&graph);

    // Add nodes (junctions/sectors)
    addNode(&graph, "Dispatch Center");
    addNode(&graph, "Sector A");
    addNode(&graph, "Sector B");
    addNode(&graph, "Sector D");
    addNode(&graph, "Emergency Site");
    addNode(&graph, "Junction C");
    addNode(&graph, "Sector E");

    // Add edges with travel times
    addEdge(&graph, "Dispatch Center", "Sector A", 10);
    addEdge(&graph, "Dispatch Center", "Sector D", 30);
    addEdge(&graph, "Sector A", "Sector B", 10);
    addEdge(&graph, "Sector B", "Emergency Site", 15);
    addEdge(&graph, "Sector D", "Emergency Site", 5);
    addEdge(&graph, "Sector B", "Junction C", 3);
    addEdge(&graph, "Junction C", "Sector E", 6);
    addEdge(&graph, "Sector E", "Emergency Site", 4);

    // Perform Dijkstra's algorithm
    dijkstra(&graph, "Dispatch Center", "Emergency Site");

    // Free allocated memory
    freeGraph(&graph);
    return 0;
}
