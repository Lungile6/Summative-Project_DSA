#ifndef GRAPH_H
#define GRAPH_H

#define MAX_DEVICES 10  // Maximum number of devices

typedef struct {
    char* devices[MAX_DEVICES]; // Array of device IDs
    int adjacencyMatrix[MAX_DEVICES][MAX_DEVICES]; // Adjacency matrix
    int deviceCount; // Current number of devices
} Graph;

// Function prototypes
void initializeGraph(Graph* graph);
int addDevice(Graph* graph, const char* deviceID);
void addConnection(Graph* graph, const char* fromDevice, const char* toDevice);
void displayConnections(Graph* graph, const char* deviceID);
void displayAdjacencyMatrix(Graph* graph);
void freeGraph(Graph* graph);

// Optional advanced features
void addBidirectionalConnection(Graph* graph, const char* deviceA, const char* deviceB);
void removeConnection(Graph* graph, const char* fromDevice, const char* toDevice);
int removeDevice(Graph* graph, const char* deviceID);
void displayIncomingConnections(Graph* graph, const char* deviceID);
void displayBothConnections(Graph* graph, const char* deviceID);

#endif // GRAPH_H
