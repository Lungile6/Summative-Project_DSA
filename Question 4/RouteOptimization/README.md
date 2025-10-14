# Route Optimization System

## Overview
This project implements a route optimization system for emergency response vehicles using Dijkstra's algorithm to find the shortest path from a dispatch center to an emergency site. The system models a road network as a graph where nodes represent junctions/sectors and edges represent roads with associated travel times.

## Features
- **Graph-based road network modeling** with bidirectional roads
- **Dijkstra's algorithm implementation** for shortest path calculation
- **Optimal route display** showing the complete path taken
- **Total travel time calculation** for emergency response planning
- **Memory-efficient adjacency list representation**

## Project Structure
```
RouteOptimization/
├── main.c          # Main program with graph setup and algorithm execution
├── graph.h         # Header file with data structures and function declarations
├── graph.c         # Graph implementation with Dijkstra's algorithm
├── README.md       # This documentation file
└── RouteOptimization # Compiled executable
```

## Data Structures

### Node Structure
```c
typedef struct Node {
    char* name;         // Name of the junction/sector
    Edge* edges;        // Linked list of connected edges
} Node;
```

### Edge Structure
```c
typedef struct Edge {
    int target;         // Target node index
    int weight;         // Travel time (weight)
    struct Edge* next;  // Pointer to next edge in adjacency list
} Edge;
```

### Graph Structure
```c
typedef struct Graph {
    Node nodes[MAX_NODES];  // Array of nodes (max 10)
    int nodeCount;          // Current number of nodes
} Graph;
```

## Algorithm Implementation

### Dijkstra's Algorithm
The implementation follows the standard Dijkstra's algorithm:

1. **Initialization**: Set all distances to infinity except start node (distance = 0)
2. **Main Loop**: For each iteration:
   - Find unvisited node with minimum distance
   - Mark node as visited
   - Update distances to adjacent nodes
3. **Path Reconstruction**: Trace back from end node using previous array
4. **Output**: Display optimal path and total travel time

### Time Complexity
- **Time**: O(V²) where V is the number of vertices
- **Space**: O(V + E) where E is the number of edges

## Usage

### Compilation
```bash
gcc -o RouteOptimization main.c graph.c
```

### Execution
```bash
./RouteOptimization
```

### Sample Output
```
Shortest path from Dispatch Center to Emergency Site:
Emergency Site Sector E Junction C Sector B Sector A Dispatch Center 
Total travel time: 33
```

## Road Network Configuration

The current implementation includes the following network:

### Nodes (Junctions/Sectors)
- Dispatch Center
- Sector A
- Sector B
- Sector D
- Emergency Site
- Junction C
- Sector E

### Roads (Bidirectional Edges)
| From | To | Travel Time |
|------|----|-----------|
| Dispatch Center | Sector A | 10 minutes |
| Dispatch Center | Sector D | 30 minutes |
| Sector A | Sector B | 10 minutes |
| Sector B | Emergency Site | 15 minutes |
| Sector D | Emergency Site | 5 minutes |
| Sector B | Junction C | 3 minutes |
| Junction C | Sector E | 6 minutes |
| Sector E | Emergency Site | 4 minutes |

## Key Functions

### Graph Management
- `initializeGraph(Graph* graph)` - Initialize empty graph
- `addNode(Graph* graph, const char* name)` - Add a new node
- `addEdge(Graph* graph, const char* from, const char* to, int weight)` - Add bidirectional edge
- `freeGraph(Graph* graph)` - Free all allocated memory

### Path Finding
- `dijkstra(Graph* graph, const char* startNode, const char* endNode)` - Find shortest path

## Memory Management
The implementation includes proper memory management:
- Dynamic allocation for node names using `strdup()`
- Dynamic allocation for edges in adjacency lists
- Complete cleanup in `freeGraph()` function
- No memory leaks

## Error Handling
- Validates node existence before adding edges
- Checks for valid start/end nodes in Dijkstra's algorithm
- Handles cases where no path exists between nodes
- Prevents exceeding maximum node limit (10 nodes)

## Extensibility
The system can be easily extended to:
- Support more nodes (increase `MAX_NODES` constant)
- Add different vehicle types with varying speeds
- Implement real-time traffic updates
- Support multiple emergency sites
- Add path visualization

## Requirements Fulfillment

### ✅ Functional Requirements
1. **Graph Modeling**: Road network modeled as graph with nodes (junctions/sectors) and edges (roads with travel times)
2. **Bidirectional Roads**: All roads are bidirectional unless otherwise specified
3. **Shortest Path Calculation**: Dijkstra's algorithm implemented for optimal path finding
4. **Program Output**: Displays optimal path and total travel time

### ✅ Technical Requirements
- Clean, modular code structure
- Proper memory management
- Error handling and validation
- Efficient algorithm implementation
- Clear documentation

## Future Enhancements
- Priority queue implementation for improved Dijkstra's performance
- Real-time traffic data integration
- Multiple emergency site support
- Path visualization with coordinates
- Database integration for persistent network data
