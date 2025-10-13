#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// Initialize the graph
void initializeGraph(Graph* graph) {
    graph->deviceCount = 0;
    for (int i = 0; i < MAX_DEVICES; i++) {
        graph->devices[i] = NULL;
        for (int j = 0; j < MAX_DEVICES; j++) {
            graph->adjacencyMatrix[i][j] = 0; // No connections initially
        }
    }
}

// Add a device to the graph
int addDevice(Graph* graph, const char* deviceID) {
    if (graph->deviceCount >= MAX_DEVICES) {
        return -1; // Maximum devices reached
    }
    graph->devices[graph->deviceCount] = strdup(deviceID); // Duplicate the device ID
    graph->deviceCount++;
    return 0; // Success
}

// Add a connection between devices
void addConnection(Graph* graph, const char* fromDevice, const char* toDevice) {
    int fromIndex = -1, toIndex = -1;

    // Find indices for fromDevice and toDevice
    for (int i = 0; i < graph->deviceCount; i++) {
        if (strcmp(graph->devices[i], fromDevice) == 0) {
            fromIndex = i;
        }
        if (strcmp(graph->devices[i], toDevice) == 0) {
            toIndex = i;
        }
    }

    if (fromIndex != -1 && toIndex != -1) {
        graph->adjacencyMatrix[fromIndex][toIndex] = 1; // Set the edge
    } else {
        printf("Invalid device ID(s).\n");
    }
}

// Display devices connected to a given device
void displayConnections(Graph* graph, const char* deviceID) {
    int deviceIndex = -1;

    // Find the index of the device
    for (int i = 0; i < graph->deviceCount; i++) {
        if (strcmp(graph->devices[i], deviceID) == 0) {
            deviceIndex = i;
            break;
        }
    }

    if (deviceIndex == -1) {
        printf("Device ID %s not found.\n", deviceID);
        return;
    }

    printf("Devices directly communicating with %s:\n", deviceID);
    for (int j = 0; j < graph->deviceCount; j++) {
        if (graph->adjacencyMatrix[deviceIndex][j] == 1) {
            printf("- %s\n", graph->devices[j]);
        }
    }
}

// Display the adjacency matrix
void displayAdjacencyMatrix(Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->deviceCount; i++) {
        for (int j = 0; j < graph->deviceCount; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Free the graph's allocated memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->deviceCount; i++) {
        free(graph->devices[i]);
    }
}

// Optional advanced features
void addBidirectionalConnection(Graph* graph, const char* deviceA, const char* deviceB) {
    addConnection(graph, deviceA, deviceB);
    addConnection(graph, deviceB, deviceA);
}

void removeConnection(Graph* graph, const char* fromDevice, const char* toDevice) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < graph->deviceCount; i++) {
        if (strcmp(graph->devices[i], fromDevice) == 0) {
            fromIndex = i;
        }
        if (strcmp(graph->devices[i], toDevice) == 0) {
            toIndex = i;
        }
    }
    if (fromIndex != -1 && toIndex != -1) {
        graph->adjacencyMatrix[fromIndex][toIndex] = 0;
    } else {
        printf("Invalid device ID(s).\n");
    }
}

int removeDevice(Graph* graph, const char* deviceID) {
    int idx = -1;
    for (int i = 0; i < graph->deviceCount; i++) {
        if (strcmp(graph->devices[i], deviceID) == 0) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        return -1; // not found
    }

    // Shift rows up (remove outgoing edges)
    for (int r = idx; r < graph->deviceCount - 1; r++) {
        for (int c = 0; c < graph->deviceCount; c++) {
            graph->adjacencyMatrix[r][c] = graph->adjacencyMatrix[r + 1][c];
        }
    }
    // Clear last row
    for (int c = 0; c < graph->deviceCount; c++) {
        graph->adjacencyMatrix[graph->deviceCount - 1][c] = 0;
    }

    // Shift columns left (remove incoming edges)
    for (int c = idx; c < graph->deviceCount - 1; c++) {
        for (int r = 0; r < graph->deviceCount; r++) {
            graph->adjacencyMatrix[r][c] = graph->adjacencyMatrix[r][c + 1];
        }
    }
    // Clear last column
    for (int r = 0; r < graph->deviceCount; r++) {
        graph->adjacencyMatrix[r][graph->deviceCount - 1] = 0;
    }

    // Free and shift deviceIDs
    free(graph->devices[idx]);
    for (int i = idx; i < graph->deviceCount - 1; i++) {
        graph->devices[i] = graph->devices[i + 1];
    }
    graph->devices[graph->deviceCount - 1] = NULL;

    graph->deviceCount--;
    return 0;
}

void displayIncomingConnections(Graph* graph, const char* deviceID) {
    int deviceIndex = -1;
    for (int i = 0; i < graph->deviceCount; i++) {
        if (strcmp(graph->devices[i], deviceID) == 0) {
            deviceIndex = i;
            break;
        }
    }
    if (deviceIndex == -1) {
        printf("Device ID %s not found.\n", deviceID);
        return;
    }
    printf("Devices sending to %s:\n", deviceID);
    for (int i = 0; i < graph->deviceCount; i++) {
        if (graph->adjacencyMatrix[i][deviceIndex] == 1) {
            printf("- %s\n", graph->devices[i]);
        }
    }
}

void displayBothConnections(Graph* graph, const char* deviceID) {
    displayConnections(graph, deviceID);
    displayIncomingConnections(graph, deviceID);
}
